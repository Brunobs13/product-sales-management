# Product and Sales Management System

## Overview

The Product and Sales Management System is a comprehensive C application designed to manage products and sales efficiently. It includes features for reading products and sales from CSV files, adding, removing, editing products, and generating sales reports. This project showcases your skills in file handling, data structures, and user interaction in C.

## Features

- **Product Management**: Add, remove, and edit product information easily.
- **Sales Tracking**: Record and manage sales transactions.
- **Automated Reporting**: Generate detailed sales reports with total sales and revenue.
- **File Handling**: Read product and sales data from CSV files.
- **User Interaction**: Simple menu-driven interface for user operations.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- CSV files containing product and sales data

### Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/product-sales-management.git
    cd product-sales-management
    ```

2. **Compile the program**:
    ```sh
    gcc main.c -o product_sales_management
    ```

3. **Ensure you have the required CSV files** (`products.csv` and `sales.csv`) in the same directory as the executable.

### Usage

1. **Run the program**:
    ```sh
    ./product_sales_management
    ```

2. **Follow the menu prompts to interact with the system**:
    - Add a new product
    - Remove an existing product
    - Edit product details
    - Generate a sales report
    - Exit the program

## CSV File Formats

### Products CSV (`products.csv`)

The file should contain product data in the following format:
```csv
code,designation,price



Example:

1,Apple,0.50
2,Banana,0.30
3,Orange,0.80

Sales CSV (sales.csv)
The file should contain sales data in the following format:

product_code,quantity,date


Example:

1,10,2024-07-19
2,5,2024-07-20
3,8,2024-07-21

## Code Structure

- ##Macros##: Define maximum limits for products and sales.
  
- ##Data Structures##: `Produto` and `Venda` structures to store product and sales data.
  
- ##Functions##:
  - `ler_produtos()`: Reads product data from a CSV file.
  - `ler_vendas()`: Reads sales data from a CSV file and updates product sales.
  - `adicionar_produto()`: Adds a new product.
  - `remover_produto()`: Removes a product by code.
  - `editar_produto()`: Edits product details.
  - `gerar_relatorio()`: Generates a sales report.
  - `main()`: Main function that drives the menu and calls other functions based on user input.


### Notes:
- **Replace** `yourusername` in the clone URL with your actual GitHub username.
- **Replace** `Your Name` and `your-email@example.com` with your actual name and email address.
- Ensure that the formatting is preserved when you paste it into your GitHub repository's README file to maintain clarity and structure.




