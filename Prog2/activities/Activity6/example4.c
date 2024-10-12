#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[100];
    float price;
    int stock;
    char productCode[20];
} Product;

Product *createProductList(int *size)
{
    *size = 0;
    Product *products = (Product *)malloc(100 * sizeof(Product));
    return products;
}

void addProduct(Product *products, int *size, const char *name, float price, int stock, const char *productCode)
{
    strcpy(products[*size].name, name);
    products[*size].price = price;
    products[*size].stock = stock;
    strcpy(products[*size].productCode, productCode);
    (*size)++;
}

void readProducts(Product *products, int size)
{
    if (size == 0)
    {
        printf("No products found.\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        printf("Product %d: Name = %s, Price = $%.2f, Stock = %d, Product Code = %s\n", i + 1, products[i].name, products[i].price, products[i].stock, products[i].productCode);
    }
}

int findProductByCode(Product *products, int size, const char *productCode)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(products[i].productCode, productCode) == 0)
        {
            return i;
        }
    }
    return -1;
}

void updateProduct(Product *products, int size, const char *productCode, const char *newName, float newPrice, int newStock)
{
    int index = findProductByCode(products, size, productCode);
    if (index != -1)
    {
        strcpy(products[index].name, newName);
        products[index].price = newPrice;
        products[index].stock = newStock;
        printf("Product with Code %s updated successfully.\n", productCode);
    }
    else
    {
        printf("Product with Code %s not found.\n", productCode);
    }
}

void deleteProduct(Product *products, int *size, const char *productCode)
{
    int index = findProductByCode(products, *size, productCode);
    if (index != -1)
    {
        for (int i = index; i < *size - 1; i++)
        {
            products[i] = products[i + 1];
        }
        (*size)--;
        printf("Product with Code %s deleted successfully.\n", productCode);
    }
    else
    {
        printf("Product with Code %s not found.\n", productCode);
    }
}

int main()
{
    int size;
    Product *products = createProductList(&size);
    int choice;

    while (1)
    {
        printf("\nPRODUCT MANAGEMENT SYSTEM\n");
        printf("1. Add Product\n");
        printf("2. Update Product by Code\n");
        printf("3. Delete Product by Code\n");
        printf("4. View All Products\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            char name[100];
            float price;
            int stock;
            char productCode[20];

            printf("Enter Name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter Price: ");
            scanf("%f", &price);
            getchar();

            printf("Enter Stock: ");
            scanf("%d", &stock);
            getchar();

            printf("Enter Product Code: ");
            fgets(productCode, sizeof(productCode), stdin);
            productCode[strcspn(productCode, "\n")] = '\0';

            addProduct(products, &size, name, price, stock, productCode);
            break;
        }
        case 2:
        {
            char productCode[20];
            char newName[100];
            float newPrice;
            int newStock;

            printf("Enter Product Code to update: ");
            fgets(productCode, sizeof(productCode), stdin);
            productCode[strcspn(productCode, "\n")] = '\0';

            printf("Enter new Name: ");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            printf("Enter new Price: ");
            scanf("%f", &newPrice);
            getchar();

            printf("Enter new Stock: ");
            scanf("%d", &newStock);
            getchar();

            updateProduct(products, size, productCode, newName, newPrice, newStock);
            break;
        }
        case 3:
        {
            char productCode[20];
            printf("Enter Product Code to delete: ");
            fgets(productCode, sizeof(productCode), stdin);
            productCode[strcspn(productCode, "\n")] = '\0';

            deleteProduct(products, &size, productCode);
            break;
        }
        case 4:
        {
            readProducts(products, size);
            break;
        }
        case 5:
        {
            printf("Exiting...\n");
            free(products);
            return 0;
        }
        default:
        {
            printf("Invalid choice. Please try again.\n");
            break;
        }
        }
    }
}