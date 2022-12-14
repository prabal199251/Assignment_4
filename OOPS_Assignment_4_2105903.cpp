#include<iostream>
#include<math.h>
using namespace std;

template<class T>                                                                               //Template
class Complex                                                                                   //Class
{
    protected:                                                                                  //Data Abstraction
    T real;
    T imag;

    public:
    Complex()                                                                                   //Constructor
    {
        real=0;
        imag=0;
    }

    Complex(T real, T imag)                                                                     //Constructor
    {
        this->real=real;
        this->imag=imag;
    }

    template<typename TT>                                                                       //Template
    friend int check_valid(Complex<TT> &C1, Complex<TT> &C2, char oper);                        //Friend Function

    template<typename TT>                                                                       //Template
    Complex<TT> operator+(Complex<TT> C)                                                        //Operator Overloading
    {
        Complex<TT> result;
        if(check_valid(*this, C, '+')==1)
        {
            result.real = real + C.real;
            result.imag = imag + C.imag;
        }
        else
        {
            cout<<"Out of range! Value assignes to 0.\n";
        }
        return result;
    }

    template<typename TT>                                                                       //Template
    Complex<TT> operator-(Complex<TT> C)                                                        //Operator Overloading
    {
        Complex<TT> result;
        if(check_valid(*this, C, '-')==1)
        {
            result.real = real - C.real;
            result.imag = imag - C.imag;
        }
        else
        {
            cout<<"Out of range! Value assignes to 0.\n";
        }
        return result;
    }

    template<typename TT>                                                                       //Template
    Complex<TT> operator*(Complex<TT> C)                                                        //Operator Overloading
    {
        Complex<TT> result;
        if(check_valid(*this, C, '*')==1)
        {
            result.real = (real * C.real) - (imag * C.imag);
            result.imag = (real * C.imag) + (imag * C.real);
        }
        else
        {
            cout<<"Out of range! Value assignes to 0.\n";
        }
        return result;
    }

    template<typename TT>                                                                       //Template
    Complex<float> operator/(Complex<TT> C)                                                     //Operator Overloading
    {
        if(check_valid(*this, C, '+')==1)
        {
            float r, i;

            r = ((real*C.real) + (imag*C.imag));
            r /= ((C.real*C.real) + (C.imag*C.imag));
            i = ((C.real*imag) - (C.imag*real));
            i /= ((C.real*C.real) + (C.imag*C.imag));

            Complex<float> result(r,i);
            return result;
        }
        else
        {
            Complex<float> result;
            cout<<"Out of range! Value assignes to 0.\n";
            return result;
        }
    }

    template<typename TT>                                                                       //Template
    friend istream& operator>>(istream &cin, Complex<TT> &C);                                   //Friend Function

    template<typename TT>                                                                       //Template
    friend ostream& operator<<(ostream &cout, Complex<TT> &C);                                  //Friend Function
};

template<typename TT>                                                                           //Template
istream& operator>>(istream &cin, Complex<TT> &C)                                               //Operator Overloading
{
    long long value;

    cout<<"\nReal Part: ";
    cin>>value;
    
        try                                                                                     //Exception Handling
        {
            if(value>pow(2, (8*sizeof(TT)-1)))
            {
                throw -1;
            }
            else
            {
                C.real=value;
            }
        }
        catch(int)
        {
            cout<<"Out of range! Value assignes to 0.\n";
        }
    
    cout<<"Imaginary Part: ";
    cin>>value;

        try                                                                                     //Exception Handling
        {
            if(value>pow(2, 8*sizeof(TT)))
            {
                throw -1;
            }
            else
            {
                C.imag=value;
            }
        }
        catch(int)
        {
            cout<<"Out of range! Value assignes to 0.\n";
        }

    return cin;
}

template<typename TT>                                                                           //Template
ostream& operator<<(ostream &cout, Complex<TT> &C)                                              //Operator Overloading
{
    if(C.real!=0)
    {
        cout<<C.real;
    }

    if(C.imag>0)
    {
        cout<<"+"<<C.imag<<"i";
    }
    else if(C.imag<0)
    {
        cout<<C.imag<<"i";
    }

    if(C.real==0&&C.imag==0)
    {
        cout<<"0";
    }

    return cout;
}

template<typename TT>                                                                           //Template
int check_valid(Complex<TT> &C1, Complex<TT> &C2, char oper)
{
    switch(oper)
    {
        case '+':
        {
            if(((long long)C1.real+C2.real)>pow(2, (8*sizeof(TT)-1))||((long long)(C1.imag+C2.imag))>pow(2, (8*sizeof(TT)-1)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
        }

        case '-':
        {
            if(((long long)C1.real-C2.real)>pow(2, (8*sizeof(TT)-1))||((long long)(C1.imag-C2.imag))>pow(2, (8*sizeof(TT)-1)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
        }

        case '*':
        {
            if(((long long)C1.real*C2.real)>pow(2, (8*sizeof(TT)-1))||((long long)(C1.imag*C2.imag))>pow(2, (8*sizeof(TT)-1)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
        }

        case '/':
        {
            if(((long long)C1.real/C2.real)>pow(2, (8*sizeof(TT)-1))||((long long)(C1.imag/C2.imag))>pow(2, (8*sizeof(TT)-1)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

int main()
{
    Complex<int> C1, C2;                                                                        //Template Object Creation
    char oper;

    cout<<"\nComplex Number Calculator\n\n";

    cout<<"Enter the First Complex Number: "; 
    cin>>C1;

    cout<<"\nEnter the Second Complex Number: "; 
    cin>>C2;

    cout<<"\nComplex number 1: ";
    cout<<C1<<endl;
    cout<<"Complex number 2: ";
    cout<<C2<<endl;
    cout<<"\n";

    cout<<"What Operation you want to perform(+, -, *, /): ";
    cin>>oper;
    cout<<"\n";

    cout<<"("<<C1<<")"<<oper<<"("<<C2<<") = (";

    switch(oper)
    {
        case '+':
        {
            Complex<int> C3;
            C3=C1+C2;
            cout<<C3;
            break;
        }

        case '-':
        {
            Complex<int> C3;
            C3=C1-C2;
            cout<<C3;
            break;
        }

        case '*':
        {
            Complex<int> C3;
            C3=C1*C2;
            cout<<C3;
            break;
        }

        case '/':
        {
            Complex<float> C3;
            C3=C1/C2;
            cout<<C3;
            break;
        }

        default:
        {
            cout<<"Invalid Operator Entered!";
            break;
        }
    }

    cout<<")";

    return 0;
}
