#include <iostream>
#include <iomanip>
using namespace std;

void menu();

bool procesoDatos(float**, int*);
void registrarProducto(float**, int*);
void listarProductos(float**, int*);
void valorInventario(float**, int*);
void buscarProducto(float**, int*);

int asignarPosicion(float**, int*);
bool codigoValido(int, float**, int*, bool evCodigoExist = true);
void expandirInvent(float***, int*);
void verificarExpansion(float***, int*);

int main()
{
    int* n = new int;
    *n = 2;

    float** inventario = new float* [*n];

    for (int i = 0; i < *n; i++)
    {
        inventario[i] = new float[3];
        for (int j = 0; j < 3; j++)
        {
            inventario[i][j] = 0;
        }
    }

    bool salir;
    do
    {
        menu();
        salir = procesoDatos(inventario, n);
        verificarExpansion(&inventario, n);
    } while (!salir);

    for (int i = 0; i < *n; i++)
    {
        delete[] inventario[i];
    }
    delete[] inventario;
    delete n;

    return 0;
}

void menu() {
    cout << "\n\tออออออออออออออออออออออออออออออออออออออออ";
    cout << "\n\t          Inventario de tienda          ";
    cout << "\n\tออออออออออออออออออออออออออออออออออออออออ";
    cout << "\n\t 1. Registrar un nuevo producto";
    cout << "\n\t 2. Lista de productos";
    cout << "\n\t 3. Calcular valor total de inventario";
    cout << "\n\t 4. Buscar producto por codigo";
    cout << "\n\t 5. Salir";
    cout << "\n\tออออออออออออออออออออออออออออออออออออออออ";
}

bool procesoDatos(float** inventario, int* n) {
    int opcion;
    do
    {
        cout << "\n\tEliga una opcion (1 - 5): "; cin >> opcion;
        if (opcion < 1 || opcion > 5)
        {
            cout << "\t> ERROR: Opcion no valida" << endl;
        }
    } while (opcion < 1 || opcion > 5);

    switch (opcion)
    {
    case 1: registrarProducto(inventario, n); break;
    case 2: listarProductos(inventario, n); break;
    case 3: valorInventario(inventario, n); break;
    case 4: buscarProducto(inventario, n); break;
    case 5: cout << "\n\t> See u next time ;)" << endl; return true;
    }

    return false;
}
void registrarProducto(float** inventario, int* n) {
    int codigo, stock;
    float precio;
    int fila;

    do
    {
        cout << "\tIngrese el codigo del producto: "; cin >> codigo;
    } while (!codigoValido(codigo, inventario, n));

    do
    {
        cout << "\tIngrese el stock del producto: "; cin >> stock;
        if (stock < 0)
        {
            cout << "\t> ERROR: El stock no puede ser negativo\n" << endl;
        }
    } while (stock < 0);

    do
    {
        cout << "\tIngrese el precio del producto: "; cin >> precio;
        if (precio < 0)
        {
            cout << "\t> ERROR: El precio no puede ser negativo\n" << endl;
        }
    } while (precio < 0);

    fila = asignarPosicion(inventario, n);
    inventario[fila][0] = codigo;
    inventario[fila][1] = stock;
    inventario[fila][2] = precio;

    cout << "\n\t> Producto registrado con exito!" << endl;
}
void listarProductos(float** inventario, int* n) {
    cout << "\n\t "
        << setw(8) << "Codigo ณ "
        << setw(7) << "Stock ณ "
        << setw(5) << "Precio"
        << endl;
    cout << "\tฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤ" << endl;

    for (int i = 0; i < *n; i++)
    {
        if (i == 0 && inventario[i][0] == 0)
        {
            cout << "\t "
                << setw(9) << "- ณ "
                << setw(8) << "- ณ "
                << setw(6) << "-"
                << endl;
        }
        if (inventario[i][0] != 0)
        {
            cout << "\t "
                << setw(6) << inventario[i][0] << " ณ "
                << setw(5) << inventario[i][1] << " ณ "
                << setw(6) << inventario[i][2]
                << endl;
        }
    }
}
void valorInventario(float** inventario, int* n) {
    float total = 0;
    for (int i = 0; i < *n; i++)
    {
        if (inventario[i][0] != 0)
        {
            total += inventario[i][1] * inventario[i][2];
        }
    }
    cout << "\n\t> El valor total del inventario es: S/" << total << endl;
}
void buscarProducto(float** inventario, int* n) {
    int codigoBucado, fila;
    bool encontrado = false;
    do
    {
        cout << "\tIngrese el codigo del producto a buscar: "; cin >> codigoBucado;
    } while (!codigoValido(codigoBucado, inventario, n, false));

    for (int i = 0; i < *n; i++)
    {
        if (inventario[i][0] == codigoBucado)
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
            << setw(8) << "Codigo ณ "
            << setw(7) << "Stock ณ "
            << setw(5) << "Precio"
            << endl;
        cout << "\tฤฤฤฤฤฤฤฤลฤฤฤฤฤฤฤลฤฤฤฤฤฤฤฤ" << endl;

        cout << "\t "
            << setw(6) << inventario[fila][0] << " ณ "
            << setw(5) << inventario[fila][1] << " ณ "
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
void expandirInvent(float*** inventario, int* n) {
    int nuevoTam = *n + 3;

    float** nuevo = new float* [nuevoTam];

    for (int i = 0; i < *n; i++) {
        nuevo[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            nuevo[i][j] = (*inventario)[i][j];
        }
    }

    for (int i = *n; i < nuevoTam; i++) {
        nuevo[i] = new float[3];
        for (int j = 0; j < 3; j++) {
            nuevo[i][j] = 0;
        }
    }

    for (int i = 0; i < *n; i++) {
        delete[](*inventario)[i];
    }
    delete[] * inventario;

    *inventario = nuevo;
    *n = nuevoTam;
}
void verificarExpansion(float*** inventario, int* n) {
    if ((*inventario)[*n - 1][0] != 0)
    {
        expandirInvent(inventario, n);
    }
}