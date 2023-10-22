#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Am definit structura pixelului
typedef struct pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} pixel;

// Am definit structura nodului din arbore
typedef struct node
{
    unsigned long long mean;
    unsigned char is_leaf;
    unsigned char avg_R;
    unsigned char avg_G;
    unsigned char avg_B;
    struct node *nw_child;
    struct node *ne_child;
    struct node *se_child;
    struct node *sw_child;

} node;

// Am definit functia care calculeaza mean ul pentru un patrat
unsigned long long mean_calc(pixel **matrix, int x, int y, int n)
{
    unsigned long long red = 0, green = 0, blue = 0, mean = 0, i, j, aux;
    // calculez suma de red,blue si green
    for (i = x; i < x + n; i++)
        for (j = y; j < y + n; j++)
        {
            red += matrix[i][j].R;
            green += matrix[i][j].G;
            blue += matrix[i][j].B;
        }
    // Aflu media de red,blue si green
    red /= (n * n);
    green /= (n * n);
    blue /= (n * n);

    for (i = x; i < x + n; i++)
        for (j = y; j < y + n; j++)
        {
            aux = (red - matrix[i][j].R);
            mean = mean + aux * aux;
            aux = (green - matrix[i][j].G);
            mean = mean + aux * aux;
            aux = (blue - matrix[i][j].B);
            mean = mean + aux * aux;
        }
    return mean / (3 * n * n);
    ;
}

// Am definit functia care creeaza arborele
void buildTree(node **root, pixel **matrix, int x, int y, int n, int tol)
{
    unsigned long long red = 0, green = 0, blue = 0, i, j;
    if (n > 1)
    { // calculez mean ul pentru patrat, si media de culoare pentru patrat
        // daca este mai mic decat tol inseamna ca este frunza
        if (mean_calc(matrix, x, y, n) <= tol)
        {
            *root = malloc(sizeof(node));
            (*root)->is_leaf = 1;

            for (i = x; i < x + n; i++)
                for (j = y; j < y + n; j++)
                {
                    red += matrix[i][j].R;
                    green += matrix[i][j].G;
                    blue += matrix[i][j].B;
                }
            (*root)->avg_R = red / (n * n);
            (*root)->avg_G = green / (n * n);
            (*root)->avg_B = blue / (n * n);
            // initializez copiii cu NULL
            (*root)->nw_child = NULL;
            (*root)->ne_child = NULL;
            (*root)->sw_child = NULL;
            (*root)->se_child = NULL;
        }
        // daca este mai mare inseamna ca nu e frunza
        if (mean_calc(matrix, x, y, n) > tol)
        {
            *root = malloc(sizeof(node));
            (*root)->is_leaf = 0;
            (*root)->mean = mean_calc(matrix, x, y, n);
            (*root)->nw_child = NULL;
            (*root)->ne_child = NULL;
            (*root)->sw_child = NULL;
            (*root)->se_child = NULL;
            buildTree(&((*root)->nw_child), matrix, x, y, n / 2, tol);
            buildTree(&((*root)->ne_child), matrix, x, y + n / 2, n / 2, tol);
            buildTree(&((*root)->se_child), matrix, x + n / 2, y + n / 2, n / 2, tol);
            buildTree(&((*root)->sw_child), matrix, x + n / 2, y, n / 2, tol);
        }
    }
}

// Am initializat functia care sa numere cate nivele sunt
int randuri(node *root)
{
    int max;
    if (root == NULL)
    {
        return 1;
    }
    else if (root->is_leaf == 1)
    {
        return 1;
    }
    else
    {

        max = 1 + randuri(root->nw_child);
        if (max < 1 + randuri(root->ne_child))
            max = 1 + randuri(root->ne_child);
        if (max < 1 + randuri(root->se_child))
            max = 1 + randuri(root->se_child);
        if (max < 1 + randuri(root->sw_child))
            max = 1 + randuri(root->sw_child);
        return max;
    }
}

// Am initializat o functie care numara cate patrate sunt
int countBlocks(node *root, int tol)
{
    int counter = 0;
    if (root == NULL)
        return 1;
    if (root->is_leaf == 0)
    {
        counter = counter + countBlocks(root->ne_child, tol);
        counter = counter + countBlocks(root->nw_child, tol);
        counter = counter + countBlocks(root->se_child, tol);
        counter = counter + countBlocks(root->sw_child, tol);
    }
    if (root->is_leaf == 1)
        counter++;
    return counter;
}

// Am initializat o functie care calculeaza dimensiunea laturii pătratului
// pentru cea mai mare zonă din imagine
int maxLenght(node *root)
{
    int min;
    if (root != NULL)
    {

        if (root->is_leaf == 0)
        {
            min = 1 + maxLenght(root->ne_child);
            if (min > 1 + maxLenght(root->nw_child))
                min = 1 + maxLenght(root->nw_child);
            if (min > 1 + maxLenght(root->sw_child))
                min = 1 + maxLenght(root->sw_child);
            if (min > 1 + maxLenght(root->se_child))
                min = 1 + maxLenght(root->se_child);
            return min;
        }
        else
            return 0;
    }
    else
        return 0;
}

// Am initializat o functie care goleste arborele
void freeTree(node *root)
{
    if (root != NULL)
    {
        freeTree(root->ne_child);
        freeTree(root->nw_child);
        freeTree(root->se_child);
        freeTree(root->sw_child);
        free(root);
    }
}

// Am initializat o functie care printeaza in binar codificarea imaginii
void PrintVector(node *root, int lvl, FILE *out_file)
{
    if (root != NULL)
    {

        if (lvl > 0)
        {
            PrintVector(root->nw_child, lvl - 1, out_file);
            PrintVector(root->ne_child, lvl - 1, out_file);
            PrintVector(root->se_child, lvl - 1, out_file);
            PrintVector(root->sw_child, lvl - 1, out_file);
        }
        if (lvl == 0)
        {
            if (root->is_leaf == 0)
            {
                fwrite(&(root->is_leaf), sizeof(unsigned char), 1, out_file);
                printf("%d\n", root->is_leaf);
            }
            else if (root->is_leaf == 1)
            {
                fwrite(&(root->is_leaf), sizeof(unsigned char), 1, out_file);
                fwrite(&(root->avg_R), sizeof(unsigned char), 1, out_file);
                fwrite(&(root->avg_G), sizeof(unsigned char), 1, out_file);
                fwrite(&(root->avg_B), sizeof(unsigned char), 1, out_file);
                printf("%d %d %d %d\n", root->is_leaf, root->avg_R, root->avg_G, root->avg_B);
            }
        }
    }
    else
        return;
}

// Am creat o functie care trece prin toate nivelele arborelului si le printeaza
void goDeeper(node *root, FILE *out_file)
{

    int max, i;
    max = randuri(root);
    for (i = 0; i < max; i++)
        PrintVector(root, i, out_file);
}

int main(int argc, char const *argv[])
{
    FILE *in_file = fopen(argv[argc - 2], "rb"); // deschide fisierul pentru citire in mod binar
    node *node = NULL;
    int i, maxim, tol;
    int bux = 1;
    unsigned int n;
    char aux[4];
    fgets(aux, 4, in_file);
    fscanf(in_file, "%d", &n);
    fscanf(in_file, "%d", &n);
    fscanf(in_file, "%d", &maxim);
    fseek(in_file, 1, SEEK_CUR);
    tol = atoi(argv[argc - 3]);
    pixel **matrix = (pixel **)malloc(n * sizeof(pixel *)); // aloca memorie pentru matrice
    for (i = 0; i < n; i++)
    {
        (matrix)[i] = (pixel *)malloc(n * sizeof(pixel));
    }

    for (i = 0; i < n; i++)
    {
        fread((matrix[i]), sizeof(pixel), n, in_file); // citeste linie cu linie din fisier si salveaza in matrice
    }
    
    fclose(in_file); // inchide fisierul
    if (strncmp(argv[argc - 4], "-c1", 3) == 0)
    {
        FILE *out_file = fopen(argv[argc - 1], "w");

        buildTree(&node, matrix, 0, 0, n, tol);

        fprintf(out_file, "%d\n", randuri(node));
        fprintf(out_file, "%d\n", countBlocks(node, tol));

        for (i = 0; i < maxLenght(node); i++)
            bux = bux * 2;
        fprintf(out_file, "%d\n", n / bux);
        fclose(out_file);
    }
    else if (strncmp(argv[argc - 4], "-c2", 3) == 0)
    {
        buildTree(&node, matrix, 0, 0, n, tol);
        FILE *out_file = fopen(argv[argc - 1], "wb");
        fwrite(&n, sizeof(unsigned int), 1, out_file);
        goDeeper(node, out_file);
        fclose(out_file);
    }
    else if (strncmp(argv[argc - 3], "-c3", 3) == 0)
    {
        printf("DA");
    }

    for (i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    freeTree(node);

    return 0;
}
