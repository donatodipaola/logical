# boolmat
The aim of **boolmat** is to provide a lightweight library for Boolean matrices operations in modern C++ (C++17).



## Usage

The **boolmat** library can be used in your project in three ways:

1. As external dependency in Bazel, pointing at its git repository;
2. Build and installed as library, then imported in your project;
3. Copied and included in your project.



### Example

```C++
#include <iostream>
#include <boolmat.hpp>

int main() {
  std::cout << "DeMorgan Law" << std::endl;
  
  boolmat::Matrix P(3,3,{0,0,1,0,1,1,1,0,0});
  boolmat::Matrix Q(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool rule1 = ((!(P+Q)) == (!P) * (!Q));
  bool rule2 = ((!(P*Q)) == (!P) + (!Q));
    
  std::cout << "P =" << P << std::endl;
  std::cout << "Q =" << Q << std::endl;
  std::cout << "rule1 = " << rule1 << std::endl;
  std::cout << "rule2 = " << rule2 << std::endl << std::endl;
  
  
  std::cout << "Transpose matrix property: (AB)^T = B^T A^T" << std::endl;
  boolmat::Matrix A(3,3,{0,0,1,0,1,1,1,0,0});
  boolmat::Matrix B(3,3,{1,0,1,0,0,0,1,1,1});
  
  bool eval =
    (boolmat::multiply(A,B).transpose() == boolmat::multiply(B.transpose(),A.transpose()));
  
  std::cout << "A =" << A << std::endl;
  std::cout << "B =" << B << std::endl;
  std::cout << "eval = " << eval << std::endl;
  
  return 0;
}
```

Output:

```terminal
DeMorgan Law
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

Let us consider the general Boolean matrix $A \in \mathbb{B}^{n\times m}$, where $\mathbb{B}$ is the Boolean set {0, 1}, $n$ is the number of rows, and $m$ the number of columns. There are two ways to create a matrix: 

1. The null-matrix constructor:

```C++
boolmat::Matrix A(3,2);
```

which builds a matrix, of given rows and columns, with all elements equal to $0$:

```terminal
A = 
0 0
0 0
0 0
```

2. The data vector constructor:

```C++
boolmat::Matrix A(3,2,{0,0,1,1,0,1});
```

which builds a matrix, of given rows and columns, with elements provided as a collections of boolean values, picked up as a sequence of rows:

```terminal
A = 
0 0
1 1
0 1
```

In case of mismatching between the matrix size and the length of the data collection provided an exception will be thrown.

Matrices in **boolmat** are constant objects, the data of a matrix cannot be modified. Thus, a new matrix has to be created as input of a expression or can be created as result of matrix operations. 

To create a matrix from an existing one, the copy constructor is provided:

```C++
boolmat::Matrix A(3,2,{0,0,1,1,0,1});
boolmat::Matrix B(A);
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
boolmat::Matrix A(3,2,{0,0,1,1,0,1});
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

You can get the value of a matrix element by using the function operator. Thus, the expression $A(i,j)$ is returning the element at the $i$-th row and $j$-th column:

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
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

### Get Matrix internal data

The matrix internal data can be also extracted, as a ```std::vector<bool>```, by using the method ```data()```:

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
std::vector<bool> data = A.data();
```

```terminal
M = 
0 1
1 0

data = 
0 1 1 0
```

Complementary, the matrix dimensions can be obtained, by using the methods ```rows()``` and ```cols()```:

```C++
boolmat::Matrix A(3,2,{0,0,1,1,0,1});
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

The basic Boolean operators ```AND```, ```OR```, and ```NOT``` are possible between matrices or between a matrix and a scalar (Boolean) value. 

### AND operator

The binary operator ```AND```, called also *logical conjunction*, is implemented via the ```*``` operator. In particular, the result of a logical conjunction of two matrices, element by element, can be obtained as: 

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
boolmat::Matrix B(2,2,{1,0,0,1});

boolmat::Matrix C = A * B;
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

Moreover, the logical conjunction of a matrix and a boolean value, element by element, can be obtained as: 

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
bool b = 1;

boolmat::Matrix C = A * b;
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

Similarly, the binary operator ```OR```, called also *logical disjunction*, is implemented via the ```+``` operator. In particular, the result of a logical disjunction of two matrices, element by element, can be obtained as: 

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
boolmat::Matrix B(2,2,{1,0,0,1});

boolmat::Matrix C = A + B;
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

Moreover, the logical conjunction of a matrix and a boolean value, element by element, can be obtained as: 

```C++
boolmat::Matrix A(2,2,{0,1,1,0});
bool b = 1;

boolmat::Matrix C = A + b;
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

Furthermore, the unary operator ```NOT```, called also *logical complement*, is implemented via the ```!``` operator: 

```C++
boolmat::Matrix A(2,2,{0,1,1,0});

boolmat::Matrix B = !A;
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
boolmat::Matrix A(2,2,{0,1,1,0});
boolmat::Matrix B(2,2,{1,0,1,0});

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

Given a matrix $A$ is possible to obtain its *transpose* $A^{T}$, which is obtained by switching the row and column indices of the matrix $A$, via the ```transpose``` method:

```C++
boolmat::Matrix A(3,2,{0,0,1,1,0,1});

boolmat::Matrix B = A.transpose();
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



###Matrix multiplication

Given two matrices $A$ and $B$,  with the number of columns in the matrix $A$ equal to the number of rows in the matrix $B$ is possible to obtain the *matrix product* $AB$, which has the number of rows of $A$ and the number of columns of $B$, via the ```multiply``` function:

```C++
boolmat::Matrix A(2,3,{1,0,0,1,0,0});
boolmat::Matrix B(3,2,{1,0,1,1,0,1});

boolmat::Matrix C = boolmat::multiply(A,B);
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


