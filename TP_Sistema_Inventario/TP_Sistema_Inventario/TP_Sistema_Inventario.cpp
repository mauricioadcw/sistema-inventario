#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

void menu();

bool procesoDatos(float**, string*, int*);
void registrarProducto(float**, string*, int*);
void listarProductos(float**, string*, int*);
void valorInventario(float**, string*, int*);
void buscarProducto(float**, string*, int*);

int asignarPosicion(float**, int*);
bool codigoValido(int, float**, int*, bool evCodigoExist = true);
bool esNumero(string);
void expandirInvent(float***, string**, int*);
void verificarExpansion(float***, string**, int*);

int main()
{
    int* n = new int;
    *n = 2;

    float** inventario = new float* [*n];
    string* nombres = new string[*n];

    for (int i = 0; i < *n; i++)
    {
        inventario[i] = new float[3];
        for (int j = 0; j < 3; j++)
        {
            inventario[i][j] = 0;
        }
        nombres[i] = "";
    }

    bool salir;
    do
    {

        menu();
        salir = procesoDatos(inventario, nombres, n);
        verificarExpansion(&inventario, &nombres, n);
    } while (!salir);

    for (int i = 0; i < *n; i++)
    {
        delete[] inventario[i];
    }
    delete[] inventario;
    delete[] nombres;
    delete n;

    return 0;
}

void menu() {
    cout << "\n\t========================================";
    cout << "\n\t          Inventario de tienda          ";
    cout << "\n\t========================================";
    cout << "\n\t 1. Registrar un nuevo producto";
    cout << "\n\t 2. Lista de productos";
    cout << "\n\t 3. Calcular valor total de inventario";
    cout << "\n\t 4. Buscar producto por codigo";
    cout << "\n\t 5. Salir";
    cout << "\n\t========================================\n";
}

bool procesoDatos(float** inventario, string* nombres, int* n) {
    string entrada;
    int opcion = 0;
    do
    {
        cout << "\tElija una opcion (1 - 5): "; cin >> entrada;
        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            opcion = stoi(entrada);
        }
        if (opcion < 1 || opcion > 5)
        {
            cout << "\t> ERROR: Opcion no valida\n" << endl;
        }
    } while (opcion < 1 || opcion > 5);

    switch (opcion)
    {
    case 1: registrarProducto(inventario, nombres, n); break;
    case 2: listarProductos(inventario, nombres, n); break;
    case 3: valorInventario(inventario, nombres, n); break;
    case 4: buscarProducto(inventario, nombres, n); break;
    case 5: cout << "\n\t> See u next time ;)" << endl; return true;
    }

    return false;
}
void registrarProducto(float** inventario, string* nombres, int* n) {
    int codigo = 0, stock = 0;
    float precio = 0.0;
    string nombre;
    string entrada;
    int fila;


    while (true)
    {
        cout << "\tIngrese el codigo del producto: "; cin >> entrada;
        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            codigo = stoi(entrada);
        }
        if (codigoValido(codigo, inventario, n))
        {
            break;
        }
    }

    while (true)
    {
        cout << "\tIngrese el stock del producto: "; cin >> entrada;
        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            stock = stoi(entrada);
        }
        if (stock < 0)
        {
            cout << "\t> ERROR: El stock no puede ser negativo\n" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "\tIngrese el precio del producto: "; cin >> entrada;
        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            precio = stof(entrada);
        }
        if (precio < 0)
        {
            cout << "\t> ERROR: El precio no puede ser negativo\n" << endl;
            continue;
        }
        break;
    }

    cin.ignore(10000, '\n');
    do
    {
        cout << "\tIngrese el nombre del producto: ";
        getline(cin, nombre);
        if (nombre == "")
        {
            cout << "\t> ERROR: El nombre no puede estar vacio\n" << endl;
        }
    } while (nombre == "");

    fila = asignarPosicion(inventario, n);
    inventario[fila][0] = codigo;
    inventario[fila][1] = stock;
    inventario[fila][2] = precio;
    nombres[fila] = nombre;

    cout << "\n\t> Producto registrado con exito!" << endl;
}
void listarProductos(float** inventario, string* nombres, int* n) {
    cout << "\n\t "
        << left
        << setw(17) << "Nombre" << " | "
        << setw(6) << "Codigo" << " | "
        << setw(5) << "Stock" << " | "
        << "Precio"
        << endl;
    cout << "\t-------------------|--------|-------|--------" << endl;
    

    for (int i = 0; i < *n; i++)
    {
        if (i == 0 && inventario[i][0] == 0)
        {
            cout << "\t "
                << left
                << setw(17) << "-" << " | "
                << right
                << setw(6) << "-" << " | "
                << setw(5) << "-" << " | "
                << setw(6) << "-"
                << endl;
        }
        if (inventario[i][0] != 0)
        {
            cout << "\t "
                << left
                << setw(17) << nombres[i] << " | "
                << setw(6) << inventario[i][0] << " | "
                << right
                << setw(5) << inventario[i][1] << " | "
                << setw(6) << inventario[i][2]
                << endl;
            
        }
    }
}
void valorInventario(float** inventario, string* nombres, int* n) {
    float total = 0;
    int cont = 0;
    cout << "\n\t "
        << left
        << setw(17) << "Nombre" << " | "
        << setw(6) << "Codigo" << " | "
        << setw(5) << "Stock" << " | "
        << setw(6) << "Precio" << " | "
        << "Valor"
        << endl;
    cout << "\t-------------------|--------|-------|--------|-------" << endl;

    for (int i = 0; i < *n; i++) {
        if (inventario[i][0] != 0) {
            cont = cont + 1;
            float valor = inventario[i][1] * inventario[i][2];
            total = total + valor;

            cout << "\t "
                << left
                << setw(17) << nombres[i] << " | "
                << setw(6) << inventario[i][0] << " | "
                << right
                << setw(5) << inventario[i][1] << " | "
                << setw(6) << inventario[i][2] << " | "
                << setw(5) << valor
                << endl;
        }
    }

    if (cont == 0) {
        cout << "\n\tNo hay productos.\n";
    }

    cout << "\n\tValor total del inventario: S/ " << total << "\n";
}
void buscarProducto(float** inventario, string* nombres, int* n) {
    int codigoBuscado = 0, fila;
    string entrada;
    bool encontrado = false;

    do
    {
        cout << "\tIngrese el codigo del producto a buscar: "; cin >> entrada;
        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            codigoBuscado = stoi(entrada);
        }
    } while (!codigoValido(codigoBuscado, inventario, n, false));

    for (int i = 0; i < *n; i++)
    {
        if (inventario[i][0] == codigoBuscado)
        {
            encontrado = true;
            fila = i;
            break;
        }
    }

    if (encontrado)
    {
        cout << "\n\t> Producto encontrado:" << endl;
        cout << "\n\t "
            << left
            << setw(17) << "Nombre" << " | "
            << setw(6) << "Codigo" << " | "
            << setw(5) << "Stock" << " | "
            << "Precio"
            << endl;
        cout << "\t-------------------|--------|-------|--------" << endl;

        cout << "\t "
            << left
            << setw(17) << nombres[fila] << " | "
            << setw(6) << inventario[fila][0] << " | "
            << right
            << setw(5) << inventario[fila][1] << " | "
            << setw(6) << inventario[fila][2]
            << endl;
    }
    else
    {
        cout << "\n\t> Sin existencias" << endl;
    }
}

int asignarPosicion(float** inventario, int* n) {
    for (int i = 0; i < *n; i++)
    {
        if (inventario[i][0] == 0)
        {
            return i;
        }
    }
    return -1;
}
bool codigoValido(int codigo, float** inventario, int* n, bool evCodigoExist) {
    if (codigo < 100000 || codigo > 999999)
    {
        cout << "\t> ERROR: El codigo debe tener seis digitos\n" << endl;
        return false;
    }
    if (evCodigoExist)
    {
        for (int i = 0; i < *n; i++)
        {
            if (inventario[i][0] == codigo)
            {
                cout << "\t> ERROR: Codigo existente\n" << endl;
                return false;
            }
        }
    }
    return true;
}
bool esNumero(string entrada) {
    bool punto = false;

    if (entrada == "" || entrada == ".") {
        cout << "\t> ERROR: Valor ingresado no valido\n" << endl;
        return false;
    }

    for (int i = 0; i < entrada.size(); i++)
    {
        char c = entrada[i];
        if (c == '.')
        {
            if (punto)
            {
                cout << "\t> ERROR: Valor ingresado no valido\n" << endl;
                return false;
            }
            punto = true;
        }
        else if (!isdigit(c))
        {
            cout << "\t> ERROR: Se esperaba un numero\n" << endl;
            return false;
        }
    }
    return true;
}
void expandirInvent(float*** inventario, string** nombres, int* n) {
    int nuevoTam = *n + 3;

    float** nuevo = new float* [nuevoTam];
    string* nuevosNombres = new string[nuevoTam];

    for (int i = 0; i < *n; i++) {
        nuevo[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            nuevo[i][j] = (*inventario)[i][j];
        }
        nuevosNombres[i] = (*nombres)[i];
    }

    for (int i = *n; i < nuevoTam; i++) {
        nuevo[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            nuevo[i][j] = 0;
        }
        nuevosNombres[i] = "";
    }

    for (int i = 0; i < *n; i++) {
        delete[](*inventario)[i];
    }
    delete[] * inventario;
    delete[] * nombres;

    *inventario = nuevo;
    *nombres = nuevosNombres;
    *n = nuevoTam;
}
void verificarExpansion(float*** inventario, string** nombres, int* n) {
    if ((*inventario)[*n - 1][0] != 0)
    {
        expandirInvent(inventario, nombres, n);
        // cout << "\t> Inventario expandido automaticamente." << endl;
    }
}