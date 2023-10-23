// Rimsha Rizvi CS 251 
// Project 4: Labyrinth Escape II - Uses google testing framework
// and implementation of a class in order to traverse a labyrinth

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct CELL {
    CELL* Next;
    T Val;
    size_t NumCols;  // total # of columns (0..NumCols-1)
    CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
      Next = _Next;
      Val = _Val;
      NumCols = _NumCols;
    }
  };

  size_t NumRows;  // total # of rows (0..NumRows-1)
  CELL** Rows;     // C array of linked lists
public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //
  Grid() {
    // initialize 4 rows
    Rows = new CELL*[4];
    NumRows = 4;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
        Rows[r] = new CELL(nullptr, T(), 4);
        CELL* cur = Rows[r];

        // create the linked list for this row.
        for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
            cur->Next = new CELL(nullptr, T());
            cur = cur->Next;
        }
    }
  }


  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  Grid(size_t R, size_t C) {
    // TO DO:  Write this parameterized constructor.
    Rows = new CELL*[R];
    NumRows = R;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; r++) {
      Rows[r] = new CELL(nullptr, T(), C);
      CELL* current = Rows[r];

    // initializing elements so it becomes their default values
      for (size_t c = 1; c < Rows[r]->NumCols; c++) {
        current->Next = new CELL(nullptr, T());
        current = current->Next;
      }
    }
  }


  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  //
  virtual ~Grid() {
    // TO DO:  Write this destructor.
    for (int r = 0; r < NumRows; r++) {
      CELL* current = Rows[r];
      CELL* previous = nullptr;
      while (current != nullptr) {
        previous = current;
        current = current->Next;
        delete previous;
      }
    }
    delete[] Rows;
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
    // TO DO:  Write this copy constructor.
//     size_t R = other.NumRows();
//     NumRows = R;
//     Rows = new CELL*[R];
    Rows = new CELL* [other.NumRows];
    NumRows = other.NumRows;

    for (size_t r = 0; r < NumRows; r++) {
      Rows[r] = new CELL(nullptr, other.Rows[r]->Val,
                         other.Rows[r]->NumCols);
      CELL* current = Rows[r];
      CELL* current_other = other.Rows[r];
      current_other = current_other->Next;

      // making linked list for above row
      for (size_t c = 1; c < Rows[r]->NumCols; c++) {
        current->Next = new CELL(nullptr, current_other->Val);
        current = current->Next;
        current_other = current_other->Next;
      }
    }
  }


  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) {
    Grid<T> temp;

    // TO DO:  Write this copy operator.
    if (this == &other) {
      return *this;
    }

    // delocating memory
    for (size_t r = 0; r < this->NumRows; r++) {
      CELL* current = Rows[r];
      CELL* previous = nullptr;
      while (current != nullptr) {
        previous = current;
        current = current->Next;
        delete previous;
      }
    }
    delete[] Rows;
    
    //size_t R = other.NumRows(); // check??????
    //NumRows = R;
    //Rows = new CELL*[R];
    Rows = new CELL *[other.NumRows];
    NumRows = other.NumRows;

    for (size_t r = 0; r < NumRows; r++) {
      Rows[r] = new CELL(nullptr, other.Rows[r]->Val,
                         other.Rows[r]->NumCols);
      CELL* current = Rows[r];
      CELL* current_other = other.Rows[r];
      current_other = current_other->Next;

      // making linked list for above row
      for (size_t c = 1; c < Rows[r]->NumCols; c++) {
        current->Next = new CELL(nullptr, current_other->Val);
        current = current->Next;
        current_other = current_other->Next;
      }
    }
    return *this;  // TO DO:  update this, it is only here so code compiles.
  }


  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //
  size_t numrows() const {
    // TO DO:  Write this function.
    return NumRows;  // TO DO:  update this, it is only here so code compiles.
  }


  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //
  size_t numcols(size_t r) const {
      // TO DO:  Write this function.
      return Rows[r]->NumCols;  // TO DO:  update this, it is only here so code compiles.

  }


  //
  // size
  //
  // Returns the total # of elements in the grid.
  //
  size_t size() const {
    // TO DO:  Write this function.
    size_t object_size = ((this->NumRows) * (this->Rows[0]->NumCols));
    return object_size;  // TO DO:  update this, it is only here so code compiles.
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) {
    //T temp;
    // TO DO:  Write this function.
    if (r < 0 || r >= NumRows || c < 0 || c >= Rows[r]->NumCols) {
//       size_t index = 0;
//       while (current != nullptr) {
//         if (index == c) {
//           return current->Val;
//         }
//         index++;
//         current = current->Next;
//       }
      throw runtime_error ("Error invalid rows/cols");
    }
      CELL* current = Rows[r];
      size_t index = 0;
      while (current != nullptr) {
        if (index == c) {
          return current->Val;
        }
        index++;
        current = current->Next;
      }
//       throw out_of_range ("Out of range");
    return current->Val;  // TO DO:  update this, it is only here so code compiles.
  }


  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //
  void _output() {
      // TO DO:  Write this function.
//       for (size_t r = 0; r < NumRows; r++) {
//         for (size_t c = 0; c < Rows[r].NumCols; c++) {
//           cout << Rows[r]->Val << ' ';
//         }
//         cout << '\n';
//       }
  }

};
