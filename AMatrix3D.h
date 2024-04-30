#ifndef NICK3D_MATRIX3D_H
#define NICK3D_MATRIX3D_H


#ifdef NICK_USE_NICK3D


#include "AVertex3D.h"
#include "AFace3D.h"

#include <math.h>


// NOTE: This is an optimized 3x4 that pretends its 4x4
class AMatrix3D {
public:
  AMatrix3D();
  void scale(float f);
  void scale(float xf, float yf, float zf);
  void translate(float x, float y, float z);
  void translateTo(float x, float y, float z);
  void xRotBy(float theta);
  void yRotBy(float theta);
  void zRotBy(float theta);
  void mult(AMatrix3D *a);  // this=this*a
  void mult(AMatrix3D *a,AMatrix3D *b);  // b=this*a
  void mult(AVertexF3D *a,AVertexF3D *b);  // b=this*a
  void mult(float *a,float *b);  // b=this*a (vertices)
  void unit();
  void transformVI(AVertexF3D *v, AVertexI3D *tv, int nvert);
  void transformVF(AVertexF3D *v, AVertexF3D *tv, int nvert);
  void transformI(float *v,int *tv,int nvert);  // vertices
  void transformF(float *v,float *tv,int nvert);  // vertices
//protected:
  float xx, xy, xz, xo;
  float yx, yy, yz, yo;
  float zx, zy, zz, zo;
};




#include <stdio.h>
#include <math.h>


#include "../cpp/alib/abaseclass.h"


#ifdef ALIB_HAVE_MATH_H
#define _USE_MATH_DEFINES 1
#include <math.h>
#endif // ALIB_HAVE_MATH_H


extern unsigned long numATMatrices;


template <class ATMatrixType>
class ATMatrix : public ABaseClass
{
  public:
    enum ATMatrixException { MEMORY, OUT_OF_RANGE, SIZE_MISMATCH, OP_NOT_SUPPORTED };
    ATMatrix<ATMatrixType> operator*(const ATMatrix<ATMatrixType>&);
    ATMatrix<ATMatrixType> operator+(const ATMatrix<ATMatrixType>&);
    ATMatrix<ATMatrixType> operator-(const ATMatrix<ATMatrixType>&);
    ATMatrix();  // Default constructor
    ATMatrix(const ATMatrix<ATMatrixType> &);  // Copy constructor
    ATMatrix(unsigned long rows, unsigned long cols);  // Constructor
    ATMatrix(unsigned long rows, unsigned long cols, ATMatrixType *data);  // Constructor
    virtual ~ATMatrix();  // Destructor
    ATMatrix& operator=(const ATMatrix<ATMatrixType> &src);
    int operator==(const ATMatrix<ATMatrixType> &src);
    //void print(ostream &dest);  // Prints a matrix
    void setElement(unsigned long, unsigned long, ATMatrixType);
    ATMatrixType getElement(unsigned long, unsigned long) const;
    ATMatrix& scale(ATMatrixType scaleFactor);
    ATMatrix& rotate(ATMatrixType xr, ATMatrixType yr, ATMatrixType zr);
    ATMatrix& translate(int xt, int yt, int zt);
    int sameSize(const ATMatrix<ATMatrixType> &);
  protected:
  private:
    unsigned long numRows, numCols;  // Matrix size
    ATMatrixType **elements;  // Matrix elements
    unsigned long ident;
    void allocResources();  // Allocates space for elements
    void freeResources();  // Deallocates space for elements
    void copyResources(const ATMatrix<ATMatrixType>&);// Copies elements into new elements
};


//template <class ATMatrixType> ATMatrix<ATMatrixType> *(ATMatrix<ATMatrixType> const &x, ATMatrix<ATMatrixType> const &y)
//{
//}


template <class ATMatrixType> ATMatrix<ATMatrixType>::ATMatrix()
{
  ident = numATMatrices++;
  //cout << "Base constructor (" << ident << ")" << endl;
  numRows = numCols = 0;  // Size is 0x0 initially
  elements = (ATMatrixType **)NULL;  // No elements
}


template <class ATMatrixType> ATMatrix<ATMatrixType>::~ATMatrix()
{
  //cout << "Base destructor (" << ident << ")" << endl;
  freeResources();  // Free matrix elements memory
  numRows = numCols = 0;  // No elements
}


template <class ATMatrixType> ATMatrix<ATMatrixType>::ATMatrix(unsigned long rows, unsigned long cols)
{
  ident = numATMatrices++;
  //cout << "Enhanced constructor (" << ident << ")" << endl;
  numRows = rows;
  numCols = cols;
  elements = (ATMatrixType **)NULL;  // No elements
  allocResources();
  for (unsigned long r=0; r<numRows; r++)
  {
    for (unsigned long c=0; c<numCols; c++)
    {
      elements[r][c] = (ATMatrixType)0;
    }
  }
}


template <class ATMatrixType>
ATMatrix<ATMatrixType>& ATMatrix<ATMatrixType>::rotate(ATMatrixType xr, ATMatrixType yr, ATMatrixType zr)
{
  if (numCols != numRows)
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw SIZE_MISMATCH;
#endif // ALIB_USE_EXCEPTIONS
  }
  //unsigned long r;
  ATMatrix<ATMatrixType> xrotation(numCols, numCols);
  xrotation.setElement(0, 0,  1);
  xrotation.setElement(1, 1,  cos((float)xr));
  xrotation.setElement(1, 2,  sin((float)xr));
  xrotation.setElement(2, 1, -sin((float)xr));
  xrotation.setElement(2, 2,  cos((float)xr));
  xrotation.setElement(3, 3,  1);
  //for (r=1; r<numCols-1; r++)  // Rotate about x-axis
  //{  xrotation.elements[r][r] = cos(xr);
  //}
  //for (r=1; r<numCols-2; r++)
  //{  xrotation.elements[r][r+1] = sin(xr);
  //  xrotation.elements[r+1][r] = -sin(xr);
  //}
  //xrotation.elements[0][0] = 1;
  //xrotation.elements[numCols-1][numCols-1] = 1;
  ATMatrix<ATMatrixType> yrotation(numCols, numCols);
  yrotation.setElement(0, 0,  cos((float)yr));
  yrotation.setElement(0, 2, -sin((float)yr));
  yrotation.setElement(1, 1,  1);
  yrotation.setElement(2, 0,  sin((float)yr));
  yrotation.setElement(2, 2,  cos((float)yr));
  yrotation.setElement(3, 3,  1);

  //for (r=0; r<numCols-1; r+=2)  // Rotate about y-axis
  //{  yrotation.elements[r][r] = cos(yr);
  //}
  //for (r=0; r<numCols-3; r++)
  //{  yrotation.elements[r][r+2] = -sin(yr);
  //  yrotation.elements[r+2][r] = sin(yr);
  //}
  //yrotation.elements[1][1] = 1;
  //yrotation.elements[numCols-1][numCols-1] = 1;
  ATMatrix<ATMatrixType> zrotation(numCols, numCols);
  zrotation.setElement(0, 0,  cos((float)zr));
  zrotation.setElement(0, 1,  sin((float)zr));
  zrotation.setElement(1, 0, -sin((float)zr));
  zrotation.setElement(1, 1,  cos((float)zr));
  zrotation.setElement(2, 2,  1);
  zrotation.setElement(3, 3,  1);
  //for (r=0; r<numCols-2; r++)  // Rotate about z-axis
  //{  zrotation.elements[r][r] = cos(zr);
  //}
  //for (r=0; r<numCols-3; r++)
  //{  zrotation.elements[r][r+1] = sin(zr);
  //  zrotation.elements[r+2][r] = -sin(zr);
  //}
  //zrotation.elements[2][2] = 1;
  //zrotation.elements[numCols-1][numCols-1] = 1;
  ATMatrix<ATMatrixType> temp=(*this) * xrotation * yrotation * zrotation;
  this->operator=(temp);
  return *this;
}


template <class ATMatrixType>
ATMatrix<ATMatrixType>& ATMatrix<ATMatrixType>::translate(int xt, int yt, int zt)
{
  ATMatrix<ATMatrixType> trans(numCols, numCols);
  trans.setElement(0, 0, 1);
  trans.setElement(1, 1, 1);
  trans.setElement(2, 2, 1);
  trans.setElement(3, 3, 1);
  trans.setElement(3, 0, xt);
  trans.setElement(3, 1, yt);
  trans.setElement(3, 2, zt);
  ATMatrix<ATMatrixType> temp=(*this) * trans;
  this->operator=(temp);
  return *this;
}


template <class ATMatrixType> ATMatrix<ATMatrixType>::ATMatrix(unsigned long rows, unsigned long cols, ATMatrixType *data)
{
  ident = numATMatrices++;
  //cout << "Enhanced constructor (" << ident << ")" << endl;
  numRows = rows;
  numCols = cols;
  elements = (ATMatrixType **)NULL;  // No elements
  allocResources();
  for (unsigned long r=0; r<numRows; r++)
  {
    for (unsigned long c=0; c<numCols; c++)
    {
      elements[r][c] = data[r*numCols+c];
    }
  }
}


template <class ATMatrixType> ATMatrix<ATMatrixType>::ATMatrix(const ATMatrix<ATMatrixType> &src)
{
  ident = numATMatrices++;
  elements = (ATMatrixType **)NULL;  // No elements
  //cout << "Copy constructor (" << ident << ")" << endl;
  copyResources(src);
}


template <class ATMatrixType> int ATMatrix<ATMatrixType>::sameSize(const ATMatrix<ATMatrixType> &m)
{
  return ((numRows == m.numRows) && (numCols == m.numCols));
}


template <class ATMatrixType> void ATMatrix<ATMatrixType>::copyResources(const ATMatrix<ATMatrixType> &src)
{
  numRows = src.numRows;
  numCols = src.numCols;
  allocResources();
  for (unsigned long r=0; r<numRows; r++)
  {
    for (unsigned long c=0; c<numCols; c++)
    {
      elements[r][c] = src.elements[r][c];
    }
  }
}


template <class ATMatrixType>
void ATMatrix<ATMatrixType>::allocResources()
{
  //cout << "Allocating Resources(" << ident << ")" << endl;
  if (elements)
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw MEMORY;
#endif // ALIB_USE_EXCEPTIONS
  }
  elements = new ATMatrixType *[numRows];
  if (!elements)
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw MEMORY;
#endif // ALIB_USE_EXCEPTIONS
  }
  for (unsigned long r=0; r<numRows; r++)
  {
    elements[r] = new ATMatrixType[numCols];
    if (!elements)
    {
#ifdef ALIB_USE_EXCEPTIONS
      throw MEMORY;
#endif // ALIB_USE_EXCEPTIONS
    }
  }
}


template <class ATMatrixType>
void ATMatrix<ATMatrixType>::freeResources()
{
  //cout << "Freeing Resources(" << ident << ")" << endl;
  for (unsigned long r=0; r<numRows; r++)
  {
    delete[] elements[r];
  }
  delete[] elements;
  elements = (ATMatrixType **)NULL;  // No elements
}


template <class ATMatrixType>
void ATMatrix<ATMatrixType>::setElement(unsigned long row, unsigned long col, ATMatrixType val)
{
  if ((row >= numRows)||(row < 0)||(col >= numCols)||(col < 0))
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw OUT_OF_RANGE;
#endif // ALIB_USE_EXCEPTIONS
  }
  elements[row][col] = val;
}


template <class ATMatrixType>
ATMatrixType ATMatrix<ATMatrixType>::getElement(unsigned long row, unsigned long col) const
{
  if ((row >= numRows)||(row < 0)||(col >= numCols)||(col < 0))
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw OUT_OF_RANGE;
#endif // ALIB_USE_EXCEPTIONS
  }
  return elements[row][col];
}


/*
template <class ATMatrixType>
void ATMatrix<ATMatrixType>::print(ostream &dest)
{
  dest << "Matrix (" << ident << ")   " << numRows << "x" << numCols << endl;
  for (int r=0; r<numRows; r++)
  { for (int c=0; c<numCols; c++)
    { dest << elements[r][c] << "  ";
    }
    dest << endl;
  }
}
*/


template <class ATMatrixType>
ATMatrix<ATMatrixType>& ATMatrix<ATMatrixType>::operator=(const ATMatrix<ATMatrixType> &src)
{
  //cout << "operator= Matrix (" << ident << ")" << endl;
  if (this != &src)
  {
    freeResources();
    copyResources(src);
  }
  return *this;
}


template <class ATMatrixType>
int ATMatrix<ATMatrixType>::operator==(const ATMatrix<ATMatrixType> &src)
{
  if (!sameSize(src))
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw SIZE_MISMATCH;
#endif // ALIB_USE_EXCEPTIONS
  }
  for (unsigned long r=0; r<numRows; r++)
  {
    for (unsigned long c=0; c<numCols; c++)
    {
      if (elements[r][c] != src.elements[r][c])
      {
        return 0;
      }
    }
  }
  return 1;
}


template <class ATMatrixType>
ATMatrix<ATMatrixType> ATMatrix<ATMatrixType>::operator*(const ATMatrix<ATMatrixType>& m2)
{
  //cout << "Multiplying" << endl;
  if (numCols != m2.numRows)
  {
   //cout << "Error: Can't multiply a "<<m1.numRows<<"x"<<m1.numCols<<
     //     " by a "<<m2.numRows<<"x"<<m2.numCols<<" matrix."<<endl;
#ifdef ALIB_USE_EXCEPTIONS
   throw ATMatrix<ATMatrixType>::SIZE_MISMATCH;
#endif // ALIB_USE_EXCEPTIONS
  }
  ATMatrix<ATMatrixType> result(numRows, m2.numCols);
  unsigned long r, c, c2;
  for (r=0; r<result.numRows; r++)
  {
    for (c=0; c<result.numCols; c++)
    {
      for (c2=0; c2<numCols; c2++)
      {
        result.elements[r][c] += elements[r][c2] * m2.elements[c2][c];
      }
    }
  }
//  dbg << "     Multiplying" << endl;
//  m1.print(dbg);
//  dbg << "         by" << endl;
//  m2.print(dbg);
//  dbg << "     Results in" << endl;
//  result.print(dbg);
  return result;
}


template <class ATMatrixType>
ATMatrix<ATMatrixType> ATMatrix<ATMatrixType>::operator+(const ATMatrix<ATMatrixType>& m2)
{
  if ((numRows != m2.numRows) || (numCols != m2.numCols))
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw ATMatrix<ATMatrixType>::SIZE_MISMATCH;
#endif // ALIB_USE_EXCEPTIONS
  }
  ATMatrix<ATMatrixType> result(numRows, numCols);
  unsigned long r, c;
  for (r=0; r<numRows; r++)
  {
    for (c=0; c<numCols; c++)
    {
      result.elements[r][c] = elements[r][c] + m2.elements[r][c];
    }
  }
  return result;
}


template <class ATMatrixType>
ATMatrix<ATMatrixType> ATMatrix<ATMatrixType>::operator-(const ATMatrix<ATMatrixType>& m2)
{
  if ((numRows != m2.numRows) || (numCols != m2.numCols))
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw ATMatrix<ATMatrixType>::SIZE_MISMATCH;
#endif // ALIB_USE_EXCEPTIONS
  }
  ATMatrix<ATMatrixType> result(numRows, numCols);
  unsigned long r, c;
  for (r=0; r<numRows; r++)
  {
    for (c=0; c<numCols; c++)
    {
      result.elements[r][c] = elements[r][c] - m2.elements[r][c];
    }
  }
  return result;
}


template <class ATMatrixType>
ATMatrix<ATMatrixType>& ATMatrix<ATMatrixType>::scale(ATMatrixType scaleFactor)
{
  if (numRows != numCols)
  {
#ifdef ALIB_USE_EXCEPTIONS
    throw OP_NOT_SUPPORTED;
#endif // ALIB_USE_EXCEPTIONS
  }
  //cout << "Scaling matrix (" << ident << ")" << endl;
  unsigned long r;
  ATMatrix<ATMatrixType> scaled(numCols, numCols);
  for (r=0; r<numCols-1; r++)
  {
    scaled.elements[r][r] = scaleFactor;
  }
  scaled.elements[r][r] = 1;
  ATMatrix<ATMatrixType> temp=(*this) * scaled;
  this->operator=(temp);
  return *this;
}


#endif // NICK_USE_NICK3D


#endif // NICK3D_MATRIX3D_H
