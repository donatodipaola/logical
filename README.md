# logical
The aim of **logical** is to provide a portable library for logical (Boolean) matrix algebra in modern C++ (C++17).





## Table of Contents

- [Usage](#usage)
  * [Example](#example)
- [Matrix creation and visualization](#matrix-creation-and-visualization)
  * [Constructors](#constructors)
  * [Stream operator](#stream-operator)
- [Matrix data](#matrix-data)
  * [Get matrix element](#get-matrix-element)
  * [Get matrix internal data](#get-matrix-internal-data)
- [Matrix operations](#matrix-operations)
  * [AND operator](#and-operator)
  * [OR operator](#or-operator)
  * [NOT operator](#not-operator)
  * [Equal operator](#equal-operator)
  * [Transpose](#transpose)
  * [Matrix Multiplication](#matrix-multiplication)



## Usage

The **logical** library can be used in two ways:

0. Copy the header file and include it in your project;
1. Add the library as dependency in your Bazel-based project:

**Bazel**

Add the repository as source in your ```WORKSPACE``` file
```Starlark
git_repository(
    name = "logical",
    remote = "https://github.com/donatodipaola/logical",
    branch = "main"
)
```
and then in the ```BUILD``` file of the component that uses the library
```Starlark
cc_binary(
    name = "yourproject",
    srcs = ["src/YourProject.cpp"],
    deps = [
         "@logical//:logical",
    ],
)
...
```



### Example

Here an example of the use of the library and the output produced.

```C++
#include <iostream>
#include <logical.hpp>

int main() {
  std::cout << "DeMorgan's Laws" << std::endl;
  
  logical::Matrix P(3,3,{0,0,1,0,1,1,1,0,0});
  logical::Matrix Q(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool rule1 = (~(P+=Q)) == ((~P) *= (~Q));
  bool rule2 = (~(P*=Q)) == ((~P) += (~Q))
    
  std::cout << "P =" << P << std::endl;
  std::cout << "Q =" << Q << std::endl;
  std::cout << "~(P+=Q)) == ((~P) *= (~Q) : eval = " << rule1 << std::endl;
  std::cout << "~(P*=Q)) == ((~P) += (~Q) : eval = " << rule2 << std::endl ;
  

  std::cout << std::endl ;
  std::cout << "Transpose matrix property: (AB)^T = B^T A^T" << std::endl;

  logical::Matrix A(3,3,{0,0,1,0,1,1,1,0,0});
  logical::Matrix B(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool eval = ((A * B).transpose() == B.transpose() * A.transpose());
  
  std::cout << "A =" << A << std::endl;
  std::cout << "B =" << B << std::endl;
  std::cout << "(A * B).transpose() == B.transpose() * A.transpose() : eval = " << eval << std::endl;
  
  return 0;
}
```

```terminal
DeMorgan's Laws
P =
0 0 1
0 1 1
1 0 0

Q =
1 0 1
0 0 0
1 1 1

rule1 = 1
rule2 = 1

Transpose matrix property: (AB)^T = B^T A^T
A =
0 0 1
0 1 1
1 0 0

B =
1 0 1
0 0 0
1 1 1

eval = 1
```



## Matrix creation and visualization

### Constructors

There are two ways to create a matrix. 

1. The null-matrix constructor

```C++
logical::Matrix A(3,2);
```

builds a matrix, of given rows and columns, with all elements equal to ```0```:

```terminal
A = 
0 0
0 0
0 0
```

2. The list initialization constructor:

```C++
logical::Matrix A(3,2,{0,0,1,1,0,1});
```

builds a matrix, of given rows and columns, with elements provided as a collection of boolean values in an initialization list:

```terminal
A = 
0 0
1 1
0 1
```

In case of mismatching between the matrix size and the length of the data collection provided an exception will be thrown.

Matrices in **logical** are constant objects, the data of a matrix cannot be modified. Thus, a new matrix has to be created as input of a expression or can be created as result of matrix operations. 

To create a matrix from an existing one, the copy constructor is provided:

```C++
logical::Matrix A(3,2,{0,0,1,1,0,1});
logical::Matrix B(A);
```

```terminal
B = 
0 0
1 1
0 1
```

### Stream operator

In order to visualize a matrix, the standard insertion stream operator is provided, so that the matrix can be sent to the console output:

```C++
logical::Matrix A(3,2,{0,0,1,1,0,1});
std::cout << "A =" << A; 
```

```terminal
A = 
0 0
1 1
0 1
```





## Matrix data

### Get matrix element

You can get the value of a matrix element by using the function operator. Thus, the expression ```A(i,j)``` is returning the element at the ```i```-th row and ```j```-th column:

```C++
logical::Matrix A(2,2,{0,1,1,0});
bool element = A(1,1);
```

```terminal
A = 
0 1
1 0

element = 
1
```

In case of a row or column index outside the matrix size an exception will be thrown.

### Get matrix internal data

The matrix internal data can be also extracted, as a ```std::vector<bool>```, by using the method ```data()```:

```C++
logical::Matrix A(2,2,{0,1,1,0});
std::vector<bool> data = A.data();
```

```terminal
M = 
0 1
1 0

data = 
0 1 1 0
```

In a complementary way, the matrix dimensions can be obtained by using the methods ```rows()``` and ```cols()```:

```C++
logical::Matrix A(3,2,{0,0,1,1,0,1});
uint8_t rows = A.rows();
uint8_t cols = A.cols();
```

```terminal
A = 
0 0
1 1
0 1

rows = 
3

cols =
2
```



## Matrix operations

The basic Boolean operators ```AND```, ```OR```, and ```NOT``` can be applied between matrices or between a matrix and a scalar (Boolean) value. 

### AND operator

The binary operator ```AND```, called also *logical conjunction*, is implemented via the ```*=``` operator. In particular, the result of a logical conjunction of two matrices, element-wise, can be obtained as: 

```C++
logical::Matrix A(2,2,{0,1,1,0});
logical::Matrix B(2,2,{1,0,0,1});

logical::Matrix C = A *= B;
```

```terminal
A = 
0 1
1 0

B = 
1 0
0 1

C =
0 0
0 0
```

In case of the two matrices are not of the same size an exception will be thrown.

Moreover, the logical conjunction of a matrix and a boolean value, element-wise, can be obtained as: 

```C++
logical::Matrix A(2,2,{0,1,1,0});
bool b = 1;

logical::Matrix C = A *= b;
```

```terminal
A = 
0 1
1 0

b = 
1

C =
0 1
1 0
```



### OR operator

Similarly, the binary operator ```OR```, called also *logical disjunction*, is implemented via the ```+=``` operator. In particular, the result of a logical disjunction of two matrices, element-wise, can be obtained as: 

```C++
logical::Matrix A(2,2,{0,1,1,0});
logical::Matrix B(2,2,{1,0,0,1});

logical::Matrix C = A += B;
```

```terminal
A = 
0 1
1 0

B = 
1 0
0 1

C =
1 1
1 1
```

In case of the two matrices are not of the same size an exception will be thrown.

Moreover, the logical conjunction of a matrix and a boolean value, element-wise, can be obtained as: 

```C++
logical::Matrix A(2,2,{0,1,1,0});
bool b = 1;

logical::Matrix C = A += b;
```

```terminal
A = 
0 1
1 0

b = 
1

C =
1 1
1 1
```



### NOT operator

Furthermore, the unary operator ```NOT```, called also *logical complement*, is implemented via the ```~``` operator: 

```C++
logical::Matrix A(2,2,{0,1,1,0});

logical::Matrix B = ~A;
```

```terminal
A = 
0 1
1 0

B =
1 0
0 1
```



### Equal operator

In order to test the equality between two matrices the equal operator ```==``` is provided:

```C++
logical::Matrix A(2,2,{0,1,1,0});
logical::Matrix B(2,2,{1,0,1,0});

bool result = A == B;
```

```terminal
A = 
0 1
1 0

B =
1 0
1 0

result =
false
```



### Transpose

Given a matrix ```A``` is possible to obtain its *transpose*, which is obtained by switching the row and column indices of the matrix, via the ```transpose``` method:

```C++
logical::Matrix A(3,2,{0,0,1,1,0,1});

logical::Matrix B = A.transpose();
```

```terminal
A = 
0 0
1 1
0 1

B =
0 1 0
0 1 1
```



### Matrix multiplication

Given two matrices ```A``` and ```B```,  with the number of columns in the matrix ```A``` equal to the number of rows in the matrix ```B``` is possible to obtain the *matrix product* ```A * B```, which has the number of rows of ```A``` and the number of columns of ```B```, via the ```*``` operator:

```C++
logical::Matrix A(2,3,{1,0,0,1,0,0});
logical::Matrix B(3,2,{1,0,1,1,0,1});

logical::Matrix C = A * B;
```

```terminal
A = 
1 0 0
1 0 0

B =
1 0
1 1
0 1

C = 
1 0
1 0
```

In case of the two matrices are not of compatible size an exception will be thrown.

