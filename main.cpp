#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <iostream>
#include "resource.h"
#include <bits/stdc++.h>
using namespace std;
HINSTANCE hInst;
int opcion=1;
double n=8;
string expresion="3x^3+4x^2+2x+5";
double aa=-2, bb=0;
// Función para evaluar una operación matemática entre dos operandos
double applyOperation(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: throw invalid_argument("Operador no soportado");
    }
}

// Función para verificar la precedencia de los operadores
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Función para manejar funciones matemáticas
double applyFunction(const string& func, double value) {
    if (func == "sin") return sin(value); // convertir grados a radianes
    if (func == "cos") return cos(value); // convertir grados a radianes
    if (func == "tan") return tan(value); // convertir grados a radianes
    if (func == "sqrt") return sqrt(value);
    throw invalid_argument("Función no soportada");
}

// Función para insertar automáticamente '*' cuando sea necesario
string preprocessExpression(const string& expression) {
    string newExpr;
    for (size_t i = 0; i < expression.length(); ++i) {
        newExpr += expression[i];
        if (i < expression.length() - 1) {
            if ((isdigit(expression[i]) || expression[i] == ')') &&
                (isalpha(expression[i + 1]) || expression[i + 1] == '(')) {
                newExpr += '*';
            }
        }
    }
    return newExpr;
}

// Función principal para evaluar una expresión matemática en notación infija con memoización
double evaluate(const string& expression, unordered_map<char, double>& variables, unordered_map<string, double>& memo) {
    if (memo.find(expression) != memo.end()) {
        return memo[expression];
    }

    stack<double> values;
    stack<char> ops;
    stack<string> funcs;

    for (size_t i = 0; i < expression.length(); i++) {
        // Ignorar espacios en blanco
        if (expression[i] == ' ') continue;

        // Si el carácter es un número, parsear el número completo
        if (isdigit(expression[i]) || expression[i] == '.') {
            string value;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                value += expression[i];
                i++;
            }
            values.push(stod(value));
            i--;
        }
        // Si el carácter es una variable o función, obtener su valor
        else if (isalpha(expression[i])) {
            string func;
            while (i < expression.length() && isalpha(expression[i])) {
                func += expression[i];
                i++;
            }
            if (func == "sin" || func == "cos" || func == "tan" || func == "sqrt") {
                funcs.push(func);
                ops.push('f');
            } else if (func.length() == 1 && variables.find(func[0]) != variables.end()) {
                values.push(variables[func[0]]);
            } else {
                cout << "Error: variable o función no definida " << func << endl;
                return 0;
            }
            i--;
        }
        // Si el carácter es un '(', añadirlo a la pila de operadores
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // Si el carácter es un ')', resolver la expresión dentro del paréntesis
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                if (ops.top() == 'f') {
                    double val = values.top();
                    values.pop();
                    string func = funcs.top();
                    funcs.pop();
                    ops.pop();
                    values.push(applyFunction(func, val));
                } else {
                    double val2 = values.top();
                    values.pop();
                    double val1 = values.top();
                    values.pop();
                    char op = ops.top();
                    ops.pop();
                    values.push(applyOperation(op, val1, val2));
                }
            }
            ops.pop(); // Remover '(' de la pila de operadores
        }
        // Si el carácter es un operador
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOperation(op, val1, val2));
            }
            ops.push(expression[i]);
        }
    }

    // Resolver los operadores restantes
    while (!ops.empty()) {
        if (ops.top() == 'f') {
            double val = values.top();
            values.pop();
            string func = funcs.top();
            funcs.pop();
            ops.pop();
            values.push(applyFunction(func, val));
        } else {
            double val2 = values.top();
            values.pop();
            double val1 = values.top();
            values.pop();
            char op = ops.top();
            ops.pop();
            values.push(applyOperation(op, val1, val2));
        }
    }

    // El resultado final es el valor restante en la pila de valores
    double result = values.top();
    memo[expression] = result; // Guardar el resultado en memo
    return result;
}

double f(double x)
{   //return x;
    //return pow(2.7182,cos(x))-2*cos(4*x)+cos(pow(x/12,5));
    //return 5*cos(10*x);
    //return sqrt(4*cos(2*x));
    unordered_map<char, double> variables;
    string expression=expresion;
    double value=x;
    unordered_map<string, double> memo;
    variables['x']=value;
    expression = preprocessExpression(expression);
    double result;
    try {
        result = evaluate(expression, variables, memo);
        //cout << "El resultado es: " << result << endl;
    } catch (const exception& e) {
        //cout << "Error al evaluar la expresión: " << e.what() << endl;
    }
    return result;
}
double g(double x)
{   //return x;
    //return pow(2.7182,cos(x))-2*cos(4*x)+cos(pow(x/12,5));
    //return 5*cos(10*x);
    //return sqrt(4*cos(2*x));
    return 9*x*x+8*x+2;
}
double parabola(double a, double b, double c, double x)
{   //return x;
    //return pow(2.7182,cos(x))-2*cos(4*x)+cos(pow(x/12,5));
    //return 5*cos(10*x);
    //return sqrt(4*cos(2*x));
    return (a*x*x)+(b*x)+c;
}
// Calcula la derivada utilizando la diferenciación hacia adelante
double forward_difference(double x, double h) {
    return (f(x + h) - f(x)) / h;
}
void DrawIntegrationRectangles(HDC hdc, RECT& drawArea, double a, double b, int n) {
    double width = (b - a) / n;
    int rectWidth = (drawArea.right - drawArea.left) / n;

    for (int i = 0; i < n; ++i) {
        double mid = a + width * (i + 0.5);
        double height = f(mid);

        // Escala la altura para que se ajuste visualmente en la ventana
        int rectHeight = (int)(height * 100);  // Escala arbitraria para visualización

        // Calcula la posición del rectángulo
        int left = drawArea.left + i * rectWidth;
        int top = drawArea.bottom - rectHeight;
        int right = left + rectWidth;
        int bottom = drawArea.bottom;

        // Dibuja el rectángulo
        Rectangle(hdc, left, top, right, bottom);
    }
}
void IntegralRectangulo(HDC hdc, int xi,int yi,int xf,int yf, double x0,double y0, double t, double a, double b){
    double base=abs(b-a)/n;
    double integralDefinida=0;
    cout<<"Por rectangulo: "<<endl;

    for (double i=0; i<n; i++){
        double altura=f(a+((base)/2)+ (base*i));
        double basex=(a+(base*i)+base);
        //cout<<basex<<" "<<altura<< " " <<n<<endl;
        integralDefinida+=abs(base*altura);

        double xp=x0+t*((a+(base*i)));
        double yp=y0-t*0;

        double xp1=x0+t*basex;
        double yp1=y0-t*altura;

        if(yp>yi&&yp<yf && yp1>yi&&yp1<yf)
            Rectangle(hdc,xp,yp,xp1,yp1);
    }
    cout<<"integral def: "<<integralDefinida<<endl;
    string pesoStr = "Integral: ";
    TextOut(hdc, 25, 200, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( integralDefinida );
    TextOut(hdc, 85, 200, pesoStr.c_str(), pesoStr.length());
}

void IntegralTrapecio(HDC hdc, int xi,int yi,int xf,int yf, double x0,double y0, double t ,double a, double b){
    double altura=abs(b-a)/n;
    double integralDefinida=0;
    cout<<"Por Trapecio: "<<endl;
    for (double i=0; i<n; i++){
        double base1 = f(a+(altura*i));
        double base2 = f(a+(altura*i)+altura);
        //double basex=base;
        double areaTrapecio = ((base1+base2)*altura)/2;

        integralDefinida+=abs(areaTrapecio);
        // x1
        double xp1=x0+t*(a+(altura*i));
        // x2
        double xp2=x0+t*(a+(altura*i)+altura);
        //y=0
        double yp=y0-t*0;
        // base 1 y 2
        double yp2=y0-t*(base1);
        double yp3=y0-t*(base2);

        if(yp>yi&&yp<yf){
            //punto 1
            MoveToEx(hdc,xp1,yp,NULL);
            LineTo(hdc,xp1,yp2);
            //punto 2
            //MoveToEx(hdc,xp1,yp2,NULL);
            LineTo(hdc,xp2,yp3);
            //punto3
            //MoveToEx(hdc,xp2,yp3,NULL);
            LineTo(hdc,xp2,yp);
            //punto4
            //MoveToEx(hdc,xp2,yp,NULL);
            LineTo(hdc,xp1,yp);
        }
    }
    cout<<"integral def: "<<integralDefinida<<endl;
    string pesoStr = "Integral: ";
    TextOut(hdc, 25, 200, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( integralDefinida );
    TextOut(hdc, 85, 200, pesoStr.c_str(), pesoStr.length());
}
double interpolacionLagrange(vector<double> x, vector<double> y, double x_valor)
{   double resultado = 0.0;
    for(int i=0;i<x.size();i++)
    {   double termino=y[i];
        for(int j=0;j<x.size();j++)
            if(j!=i)
                termino*=(x_valor-x[j])/(x[i]-x[j]);
        resultado += termino;
    }
    return resultado;
}

void IntegralSimpson(HDC hdc, int xi,int yi,int xf,int yf, double x0,double y0, double t, double xri, double xrf, double var, double a, double b){
    if(int(n)%2!=0)
        return;
    double base=abs(b-a)/n;
    double delta=(b-a)/n;
    double integralDefinida=0;
    cout<<"Por Simpson: "<<endl;
    for(double i=0; i<=n; i++){
        if(i==0){
            integralDefinida+=abs(f(a+(base*i)));
        }
        else if(i==n || int(i)%2==0){
            if(i==n)
                integralDefinida+=abs(f(a+(base*i)));
            else{
                integralDefinida+=abs(2*f(a+(base*i)));
            }
            //en x
            double inicio=(a+(base*(i-2)));
            double medio=a+(base*(i-1));
            //double finAhora=((a+(base*i)==0))? 1 :  (a+(base*i));
            double finAhora=(a+(base*i));
            double xa=x0+t*(inicio);
            double xb=x0+t*(finAhora);
            vector <double> x = {inicio, medio, finAhora};
            vector <double> y = {f(inicio),f(medio), f(finAhora)};
            //pra(x,y,hdc,x0,y0, t);
            for(double xx=xri;xx<=xrf;xx+=var)
            {   double yy=interpolacionLagrange(x, y, xx);
                double xp=x0+t*xx;
                double yp=y0-t*yy;
                if(yp>yi&&yp<yf && xa<=xp && xb>=xp)
                    SetPixel(hdc,xp,yp,RGB(0,255,0));
            }
            for(int i=0;i<x.size();i++)
            {   Ellipse(hdc,x[i]-3,y[i]-3,x[i]+3,y[i]+3);
            }
        }
        else{
            integralDefinida+=abs(4*f(a+(base*i)));
        }
    }
    integralDefinida*=delta/3;
    cout<<"integral def: "<<integralDefinida<<endl;
    string pesoStr = "Integral: ";
    TextOut(hdc, 25, 200, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( integralDefinida );
    TextOut(hdc, 85, 200, pesoStr.c_str(), pesoStr.length());
}
void IntegralMontecarlo(HDC hdc, int xi,int yi,int xf,int yf, double x0,double y0, double t, double a, double b){
    srand(time(NULL));

    double M=f(b);
    double xp0=x0+t*a;
    double yy=(f(a)<0)? f(a):0;
    double yp0=y0-t*yy;

    double xp1=x0+t*(b);
    double yp1=y0-t*(M);

    Rectangle(hdc,xp0,yp0,xp1,yp1);
    int Exitos=0;
    double integralDefinida=0;
    cout<<"Por Montecarlo: "<<endl;

    for (double i=0; i<n; i++){
        double x = a + ((double)rand() / RAND_MAX) * (b - a);
        double y = yy + ((double)rand() / RAND_MAX) * (f(b) - yy);
        if(y<= f(x))
            Exitos++;
        double xp=x0+t*x;
        double yp=y0-t*y;
        SetPixel(hdc,xp,yp,RGB(0,0,255));
    }
    integralDefinida=(Exitos/n)*(b-a)*M;
    cout<<"integral def: "<<integralDefinida<<endl;
    string pesoStr = "Integral: ";
    TextOut(hdc, 25, 200, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( integralDefinida );
    TextOut(hdc, 85, 200, pesoStr.c_str(), pesoStr.length());
}
void texto(HDC hdc, double a, double b){
    string pesoStr = "a: ";
    TextOut(hdc, 100, 20, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( a );
    TextOut(hdc, 115, 20, pesoStr.c_str(), pesoStr.length());
    pesoStr = "b: ";
    TextOut(hdc, 100, 50, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( b );
    TextOut(hdc, 115, 50, pesoStr.c_str(), pesoStr.length());
    pesoStr = "n: ";
    TextOut(hdc, 100, 80, pesoStr.c_str(), pesoStr.length());
    pesoStr = to_string( n );
    TextOut(hdc, 115, 80, pesoStr.c_str(), pesoStr.length());
}
void Dibujar(HDC hdc,int xi,int yi,int xf,int yf)
{
    int x0=(xf+xi)/2, y0=(yf+yi)/2;
    double xri=-10,xrf=10,var=0.001;
    double t=(xf-xi)/(xrf-xri);
    Rectangle(hdc,xi,yi,xf,yf);
    MoveToEx(hdc,xi,y0,NULL);
    LineTo(hdc,xf,y0);
    MoveToEx(hdc,x0,yi,NULL);
    LineTo(hdc,x0,yf);

    texto(hdc, aa, bb);

    for(double xr=xri;xr<=xrf;xr+=var)
    {   double yr=f(xr);

        double xp=x0+t*xr;
        double yp=y0-t*yr;
        if(yp>yi&&yp<yf)
            SetPixel(hdc,xp,yp,RGB(255,0,0));
    }
    switch(opcion){
        case 1:
            IntegralRectangulo(hdc, xi, yi, xf, yf, x0, y0, t, aa, bb);
        break;
        case 2:
            IntegralTrapecio(hdc, xi, yi, xf, yf, x0, y0, t, aa, bb);
        break;
        case 3:
            IntegralSimpson(hdc, xi, yi, xf, yf, x0, y0, t, xri, xrf, var, aa, bb);
        break;
        case 4:
            IntegralMontecarlo(hdc, xi, yi, xf, yf, x0, y0, t, aa, bb);
        break;
    }

}
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {   case WM_PAINT:
        {   PAINTSTRUCT ps;
            HDC hdc;
            hdc=BeginPaint(hwndDlg,&ps);
            Dibujar(hdc,10,10,1000,800);
            //DrawIntegrationRectangles(hdc, ps.rcPaint, 0.0, 1.0, 10);

            EndPaint(hwndDlg,&ps);
        }
        return TRUE;
        case WM_INITDIALOG:
        {
        }
        return TRUE;
        case WM_CLOSE:
        {   EndDialog(hwndDlg, 0);
        }
        return TRUE;
        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {
                case BOTON1:
                {
                    opcion=1;
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON2:
                {   opcion=2;
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON3:
                {   opcion=3;
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON4:
                {   opcion=4;
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON5:
                {
                    char Cad[10];
                    GetDlgItemText(hwndDlg,N,Cad, 10);
                    n = abs(atof(Cad));
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON6:
                {
                    char Cad[20];
                    GetDlgItemText(hwndDlg,EXP,Cad, 20);
                    string exp(Cad);
                    expresion=exp;
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON7:
                {
                    char Cad[20];
                    GetDlgItemText(hwndDlg,A,Cad, 20);
                    aa = stof(Cad);
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
                case BOTON8:
                {
                    char Cad[20];
                    GetDlgItemText(hwndDlg,B,Cad, 20);
                    bb = stof(Cad);
                    InvalidateRect(hwndDlg,NULL,true);
                }
                return TRUE;
            }
        }
        return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
