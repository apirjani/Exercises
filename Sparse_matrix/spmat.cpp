#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "spmat.h"
using namespace std;

#ifdef SPARSE_DEBUG
#include "spmat-debug.h"    
// global instance of the debug helper
SparseMatrixDebugHelper debug;
#endif


// Define and initialize the constant static member npos here
const size_t SparseMatrix::npos = (size_t)-1;



// ----------------------------------------------------------------------------
// ------------------ Coord struct Implementation -----------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::Coord::Coord(size_t row, size_t col) :
    r(row), c(col)
{
}

// operator[] accessors
size_t& SparseMatrix::Coord::operator[](size_t index) {
    if (index == ROW)
    {
        return r;
    }

    else if (index == COL)
    {
        return c;
    }

    else
    {
        throw std::out_of_range("Invalid index");
    }

}

size_t const& SparseMatrix::Coord::operator[](size_t index) const {
    if (index == ROW)
    {
        return r;
    }

    else if (index == COL)
    {
        return c;
    }

    else
    {
        throw std::out_of_range("Invalid index");
    }

}

// operator== comparison function
bool SparseMatrix::Coord::operator==(const Coord& rhs) const {
    if (r == rhs.r && c == rhs.c)
    {
        return true;
    }

    else
    {
        return false;
    }
}


// operator != comparison function
// COMPLETE
bool SparseMatrix::Coord::operator!=(const Coord& rhs) const
{
    return !operator==(rhs);
}

// ----------------------------------------------------------------------------
// ------------------ SparseItem struct Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::SparseItem::SparseItem(Coord coord, double v)
{
    this->val = v;
    this->coord = coord;
    this->prev[ROW] = this->prev[COL] = nullptr;
    this->next[ROW] = this->next[COL] = nullptr;
}

// ----------------------------------------------------------------------------
// ----------------- SparseMatrix class Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
SparseMatrix::SparseMatrix(size_t n) : 
     n_(n)
{
    if(0U == n_) {
        throw std::invalid_argument("n must be greater than 0");
    }
    /* Add code as needed */
    lists_[ROW] = new SparseItem*[n];
    lists_[COL] = new SparseItem*[n];
    for (size_t i = 0; i < n_; i++)
    {
        lists_[ROW][i] = nullptr;
        lists_[COL][i] = nullptr;
    }

}

// Destructor
SparseMatrix::~SparseMatrix() 
{
    //for each row head pointer and col head pointer, delete the items in their lists
    for (size_t i = 0; i < n_; i++)
    {
        while (lists_[ROW][i] != nullptr)
        {
            deleteNode(lists_[ROW][i]);
        }

        while (lists_[COL][i] != nullptr)
        {
            deleteNode(lists_[COL][i]);
        }

    }

    //delete the row and col head pointers themselves
    delete[] lists_[ROW];
    delete[] lists_[COL];

}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::createSparseItem(const SparseMatrix::Coord& coord, double val)
{
    SparseItem* ptr = new SparseItem(coord, val);
#ifdef SPARSE_DEBUG    
    debug.addItem(ptr);
#endif
    return ptr;
}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::lowerBound(size_t list, Coord target_coord ) const
{
    SparseItem* head = this->lists_[list][target_coord[list]];
    size_t target_index = target_coord[1-list];

    if(head == nullptr) {
        return nullptr;
    }
    else if( head->coord[1-list] > target_index ) {
        return nullptr;
    }
    else {
        while(  head->next[list] != nullptr && 
                head->next[list]->coord[1-list] <= target_index  ) 
        {
            head = head->next[list];
        }
        return head;        
    }
}


// COMPLETED
double SparseMatrix::get(const Coord& coord) const
{
    if( coord[ROW] >= n_ || coord[COL] >= n_ ) {
        throw std::invalid_argument("Bad coordinates");
    }
    SparseItem* head = lowerBound(ROW, coord);
    if(nullptr == head || head->coord[COL] != coord[COL]){
        return 0;
    }
    return head->val;
}

// COMPLETED
void SparseMatrix::print(std::ostream &os) const
{
    os << setprecision(7);
    for(size_t r = 0; r < this->n_; r++) {
        SparseItem* ptr = this->lists_[ROW][r];
        size_t col = 0;
        while(ptr != NULL) {
            while(col < ptr->coord[COL]) {
                os << setw(8) << 0;
                col++;
            }
            os << setw(8) << ptr->val;
            col++;
            ptr = ptr->next[ROW];
        }
        while(col < this->n_) {
            os << setw(8) << 0;
            col++;
        }
        os << endl;
    }
}


void SparseMatrix::deleteNode(SparseItem* node)
{

    if(nullptr == node){
        throw std::invalid_argument("argument must not be null");
    }

    //if first item in row list, header should point to what node was pointing to
    if (node->prev[ROW] == nullptr)
    {
        lists_[ROW][node->coord[ROW]] = node->next[ROW];
        //if there was node following the one deleted, then make its previous pointer null
        if (lists_[ROW][node->coord[ROW]] != nullptr)
        {
            lists_[ROW][node->coord[ROW]]->prev[ROW] = nullptr;
        }
    }

    else
    {
        //let preceding sparseitem point to the sparseitem after the one being removed
        (node->prev[ROW])->next[ROW] = node->next[ROW];
        //only make following sparseitem point to the preceding sparseitem if there exists a following one
        //or else we would dereference nullptr if node was last item in list
        if (node->next[ROW] != nullptr)
        {
            (node->next[ROW])->prev[ROW] = node->prev[ROW];
        }
    }

    //if first item in column list
    if (node->prev[COL] == nullptr)
    {
        lists_[COL][node->coord[COL]] = node->next[COL];
        if (lists_[COL][node->coord[COL]] != nullptr)
        {
            lists_[COL][node->coord[COL]]->prev[COL] = nullptr;
        }
    }

    else
    {
        (node->prev[COL])->next[COL] = node->next[COL];
        if (node->next[COL] != nullptr)
        {
            (node->next[COL])->prev[COL] = node->prev[COL];
        }
    }

    
    
#ifdef SPARSE_DEBUG    
    debug.deleteItem(node);
#endif
    delete node;
    
}

void SparseMatrix::set(const Coord& coord, double val)
{
    if (coord[ROW] < 0 || coord[ROW] > n_-1 || coord[COL] < 0 || coord[COL] > n_-1)
    {
        throw std::out_of_range("Coordinate provided is out of range");
    }
    //if cell is empty
    if (get(coord) == 0)
    {
        //and the value we want to put in new cell is not 0
        if (val != 0)
        {
            //store item before the one we want to add (if exists)
            SparseItem* PrevSparseItem_Row = lowerBound(ROW, coord);
            //create new item using given coord and val
            SparseItem* NewSparseItem = createSparseItem(coord, val);
            //either empty list or new item comes before first item in list
            if (PrevSparseItem_Row == nullptr)
            {
                //if empty list
                if (lists_[ROW][coord[ROW]] == nullptr)
                {
                    lists_[ROW][coord[ROW]] = NewSparseItem;
                }
                //if new item comes before first item already in list
                else
                {
                    NewSparseItem->next[ROW] = lists_[ROW][coord[ROW]];
                    (lists_[ROW][coord[ROW]])->prev[ROW] = NewSparseItem;
                    lists_[ROW][coord[ROW]] = NewSparseItem;
                }
            }
            //if list exists and new item comes after first item
            else
            {
                NewSparseItem->next[ROW] = PrevSparseItem_Row->next[ROW];
                NewSparseItem->prev[ROW] = PrevSparseItem_Row;
                PrevSparseItem_Row->next[ROW] = NewSparseItem;
                //only change prev of following item if it exists; check so we don't dereference null pointer
                if (NewSparseItem->next[ROW] != nullptr)
                {
                    (NewSparseItem->next[ROW])->prev[ROW] = NewSparseItem;
                }
            }
            //do same thing for column list
            //store item before the one we want to add (if exists)
            SparseItem* PrevSparseItem_Col = lowerBound(COL, coord);
            //either empty list or new item comes before first item in list
            if (PrevSparseItem_Col == nullptr)
            {
                //if empty list
                if (lists_[COL][coord[COL]] == nullptr)
                {
                    lists_[COL][coord[COL]] = NewSparseItem;
                }
                //if new item comes before first item already in list
                else
                {
                    NewSparseItem->next[COL] = lists_[COL][coord[COL]];
                    (lists_[COL][coord[COL]])->prev[COL] = NewSparseItem;
                    lists_[COL][coord[COL]] = NewSparseItem;
                }
            }
            //if list exists and new item comes after first item
            else
            {
                NewSparseItem->next[COL] = PrevSparseItem_Col->next[COL];
                NewSparseItem->prev[COL] = PrevSparseItem_Col;
                PrevSparseItem_Col->next[COL] = NewSparseItem;
                //only change prev of following item if it exists; check so we don't dereference null pointer
                if (NewSparseItem->next[COL] != nullptr)
                {
                    (NewSparseItem->next[COL])->prev[COL] = NewSparseItem;
                }
            }

        }
    }
    //if cell already exists (non-zero)
    else
    {
        if (val != 0)
        {
            SparseItem* ExistingSparseItem = lowerBound(ROW, coord);
            ExistingSparseItem->val = val;
        }

        else
        {
            //call delete node
            SparseItem* ExistingSparseItem = lowerBound(ROW, coord);
            deleteNode(ExistingSparseItem);

        }

    }


#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif
}


double SparseMatrix::sumDim(const Coord& coord) const
{
    double sum = 0;
    //if row value is not npos, we should iterate through that row

    if (coord[ROW] != SparseMatrix::npos && coord[COL] == SparseMatrix::npos && (coord[ROW] >= 0 && coord[ROW] <= n_-1))
    {
        SparseItem* temp = lists_[ROW][coord[ROW]];
        //iterate through row until we get to end of list, summing up values of each item
        while (temp != nullptr)
        {
            sum += temp->val;
            temp = temp->next[ROW];
        }
    }
    //if col value is not npos, we should iterate through that col
    else if (coord[COL] != SparseMatrix::npos && coord[ROW] == SparseMatrix::npos && (coord[COL] >= 0 && coord[COL] <= n_-1))
    {
        SparseItem* temp = lists_[COL][coord[COL]];
        while (temp != nullptr)
        {
            sum += temp->val;
            temp = temp->next[COL];
        }
    }

    //invalid input (either we don't have an npos value or other coord value is out of range)
    else
    {
        if (coord[COL] != SparseMatrix::npos && coord[ROW] != SparseMatrix::npos)
        {
            throw std::invalid_argument("One of the coordinate values must be npos");

        }

        else
        {
            throw std::out_of_range("Other coordinate value is not between 0 and n-1");
        }
    }

    return sum;

}

void SparseMatrix::copyDim(const Coord& srcCoord, const Coord& dstCoord)
{
    // Ignore self-copy - leave these as the first lines of the function 
    if( dstCoord == srcCoord) {
        return;
    }

    // Add code to check for exception cases and, if valid, perform the copy
    // of the indicated dimension

    //check if one of the coordinates from each source and dest are npos
    if (!((srcCoord[ROW] == SparseMatrix::npos || srcCoord[COL] == SparseMatrix::npos) && 
    (dstCoord[ROW] == SparseMatrix::npos || dstCoord[COL] == SparseMatrix::npos)))
    {
        throw std::invalid_argument("One coordinate in srcCoord and one coordinate in dstCoord must be npos");
    }

    //check if coordinates are in bounds
    if ((srcCoord[ROW] == SparseMatrix::npos && (srcCoord[COL] < 0 || srcCoord[COL] > n_-1)) || 
    (srcCoord[COL] == SparseMatrix::npos && (srcCoord[ROW] < 0 || srcCoord[ROW] > n_-1)) || 
    (dstCoord[ROW] == SparseMatrix::npos && (dstCoord[COL] < 0 || dstCoord[COL] > n_-1)) ||
    (dstCoord[COL] == SparseMatrix::npos && (dstCoord[ROW] < 0 || dstCoord[ROW] > n_-1)))
    {
        throw std::out_of_range("One or more of the coordinates are out of bounds");
    }

    //if row value of destination is not npos and is within bounds
    if (dstCoord[ROW] != SparseMatrix::npos && dstCoord[COL] == SparseMatrix::npos 
    && dstCoord[ROW] >= 0 && dstCoord[ROW] <= n_-1)
    {
        //if source is a row (row to row copy)
        if (srcCoord[ROW] != SparseMatrix::npos && srcCoord[COL] == SparseMatrix::npos && srcCoord[ROW] >= 0 && srcCoord[ROW] <= n_-1)
        {
            //first let's delete the existing list at destination row
            SparseItem* temp_delete = lists_[ROW][dstCoord[ROW]];
            while (temp_delete != nullptr)
            {
                SparseItem* temp_delete_next = temp_delete->next[ROW];
                deleteNode(temp_delete);
                temp_delete = temp_delete_next;
            }

            //get pointer to head of source row
            SparseItem* temp_row_source = lists_[ROW][srcCoord[ROW]];
            //iterate through source row and copy each value over to destination row
            while (temp_row_source != nullptr)
            {
                Coord set_location(dstCoord[ROW], temp_row_source->coord[COL]);
                set(set_location, temp_row_source->val);
                temp_row_source = temp_row_source->next[ROW];
            }
        }

        //if source is a column (column to row copy)
        else if (srcCoord[COL] != SparseMatrix::npos && srcCoord[ROW] == SparseMatrix::npos 
        && srcCoord[COL] >= 0 && srcCoord[COL] <= n_-1)
        {
            //let's delete the existing list at dest row
            SparseItem* temp_delete = lists_[ROW][dstCoord[ROW]];
            while (temp_delete != nullptr)
            {
                //make sure not to delete items at the intersection
                SparseItem* temp_delete_next = temp_delete->next[ROW];
                if (temp_delete->coord[COL] != srcCoord[COL])
                {
                    deleteNode(temp_delete);
                }

                temp_delete = temp_delete_next;          
                
            }
            
            //get pointer to head of source col
            SparseItem* temp_col_source = lists_[COL][srcCoord[COL]];
            //pointer for case where next item is intersect
            SparseItem* intersect = nullptr;
            //pointer for case where current item is intersect
            SparseItem* intersect_current = nullptr;
            Coord intersect_coord(dstCoord[ROW], srcCoord[COL]);
            double replace_value = 0;
            //in special case where intersect is zero or is not being 
            //pointed to by item with replace value
            bool intersect_is_not_next = false;
            bool intersect_already_passed = false;
            //iterate through the source column
            while (temp_col_source != nullptr)
            {
                //if the following item is at intersection, don't set the value yet
                //just save the value and a pointer to that item to replace value later
                if (temp_col_source->next[COL] != nullptr && (temp_col_source->next[COL])->coord[ROW] == dstCoord[ROW])
                {
                    //set value if next item is at intersection but that's not where next value is being set at
                    if (temp_col_source->coord[ROW] != (temp_col_source->next[COL])->coord[COL])
                    {
                        Coord set_location(dstCoord[ROW], temp_col_source->coord[ROW]);
                        set(set_location, temp_col_source->val);
                    }
                    //if you will overwrite the intersect, save its location and the previous value and skip
                    else
                    {
                        intersect = temp_col_source->next[COL];
                        replace_value = temp_col_source->val;
                    }
                }

                //if you're currently at intersect, save location, set next value to intersect's value
                else if (temp_col_source->coord[ROW] == dstCoord[ROW])
                {
                    intersect_current = temp_col_source;
                    Coord set_location(dstCoord[ROW], intersect_current->coord[ROW]);
                    set(set_location, intersect_current->val);
                    intersect_already_passed = true;

                }

                //in the case that you're not at intersect, and it's not next
                else
                {
                    Coord set_location(dstCoord[ROW], temp_col_source->coord[ROW]);
                    //if you're not going to overwrite the intersect, or if we already copied its value over
                    if (set_location != intersect_coord || intersect_already_passed)
                    {
                        set(set_location, temp_col_source->val);
                    }
                    //otherwise, store the current value as the replace value and note that intersect isn't next
                    else
                    {
                        replace_value = temp_col_source->val;
                        intersect_is_not_next = true;
                    }
                }

                temp_col_source = temp_col_source->next[COL];
            }

            //now set the value of the item at the intersect with the value of item before it
            if (intersect != nullptr)
            {
                intersect->val = replace_value;
            }

            //if intersect needs to be 0, take care of that now
            if (intersect_current != nullptr && get({intersect_current->coord[COL], srcCoord[COL]}) == 0)
            {
                set(intersect_current->coord, 0);
            }

            //if intersect was never the next item (possibly because it was zero)
            if (intersect_is_not_next)
            {
                set(intersect_coord, replace_value);
            }

        }
        
    }

    //if col value of dest is not npos and is within bounds
    else if (dstCoord[COL] != SparseMatrix::npos && dstCoord[ROW] == SparseMatrix::npos 
    && dstCoord[COL] >= 0 && dstCoord[COL] <= n_-1)
    {
        //if source is a column (column to column copy)
        if (srcCoord[COL] != SparseMatrix::npos && srcCoord[ROW] == SparseMatrix::npos 
        && srcCoord[COL] >= 0 && srcCoord[COL] <= n_-1)
        {
            //first let's delete the existing list at destination col
            SparseItem* temp_delete = lists_[COL][dstCoord[COL]];
            while (temp_delete != nullptr)
            {
                SparseItem* temp_delete_next = temp_delete->next[COL];
                deleteNode(temp_delete);
                temp_delete = temp_delete_next;
            }

            SparseItem* temp_col_source = lists_[COL][srcCoord[COL]];
            while (temp_col_source != nullptr)
            {
                Coord set_location(temp_col_source->coord[ROW], dstCoord[COL]);
                set(set_location, temp_col_source->val);
                temp_col_source = temp_col_source->next[COL];
            }

        }

        //if source is a row (row to column copy)
        else if (srcCoord[ROW] != SparseMatrix::npos && srcCoord[COL] == SparseMatrix::npos 
        && srcCoord[ROW] >= 0 && srcCoord[ROW] <= n_-1)
        {
            SparseItem* temp_delete = lists_[COL][dstCoord[COL]];
            while (temp_delete != nullptr)
            {
                SparseItem* temp_delete_next = temp_delete->next[COL];
                if (temp_delete->coord[ROW] != srcCoord[ROW])
                {
                    deleteNode(temp_delete);
                }

                temp_delete = temp_delete_next;
                
            }

            SparseItem* temp_row_source = lists_[ROW][srcCoord[ROW]];
            SparseItem* intersect = nullptr;
            SparseItem* intersect_current = nullptr;
            Coord intersect_coord(srcCoord[ROW], dstCoord[COL]);
            double replace_value = 0;
            bool intersect_is_not_next = false;
            bool intersect_already_passed = false;
            while (temp_row_source != nullptr)
            {
                if (temp_row_source->next[ROW] != nullptr && (temp_row_source->next[ROW])->coord[COL] == dstCoord[COL])
                {
                    
                    if (temp_row_source->coord[COL] != (temp_row_source->next[ROW])->coord[ROW])
                    {
                        Coord set_location(temp_row_source->coord[COL], dstCoord[COL]);
                        set(set_location, temp_row_source->val);
                    }

                    else
                    {
                        intersect = temp_row_source->next[ROW];
                        replace_value = temp_row_source->val;
                    }

                }

                else if (temp_row_source->coord[COL] == dstCoord[COL])
                {
                    intersect_current = temp_row_source;
                    Coord set_location(intersect_current->coord[COL], dstCoord[COL]);
                    set(set_location, intersect_current->val);
                    intersect_already_passed = true;
                    
                }

                else
                {
                    Coord set_location(temp_row_source->coord[COL], dstCoord[COL]);
                    if (set_location != intersect_coord || intersect_already_passed)
                    {
                        set(set_location, temp_row_source->val);
                    }

                    else
                    {
                        replace_value = temp_row_source->val;
                        intersect_is_not_next = true;         
                    }
                    
                }

                temp_row_source = temp_row_source->next[ROW];
            }

            if (intersect != nullptr)
            {
                intersect->val = replace_value;
            }

            if (intersect_current != nullptr && get({intersect_current->coord[ROW], srcCoord[ROW]}) == 0)
            {
                set(intersect_current->coord, 0);
            }

            if (intersect_is_not_next)
            {
                set(intersect_coord, replace_value);
            }

        }

    }
    

#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif
}

