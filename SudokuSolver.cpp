#include <iostream>
#include <vector>


std::vector<std::vector<char> > sud_to_vec_vec(std::array<char,81> sudoku){
    std::vector<std::vector<char> > output;
    output.reserve(9);
    for(int i = 0; i < 9; i++){
        std::vector<char> input;
        input.reserve(9);
        for(int j = i*9; j < i*9+9; j++){
            input.push_back(sudoku[j]);
        }
        output.push_back(input);
    }
    return output;
}

void print_sudoku(std::vector<std::vector<char> > sudoku){
    bool first = true;
    for(int i = 0; i < 9; i++){
        bool first = true;
        for(int j = 0; j < 9; j++){
            if(first){
                std::cout << sudoku[i][j];
                first = false;
                continue;
            }
            std::cout << ", " << sudoku[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool search_row(std::vector<std::vector<char> > grid,int r,char k){
        for(char ch : grid[r]){
            if(ch == k){
                return false;
            }
        }
        return true;
    }

bool search_column(std::vector<std::vector<char> > grid,int c, char k){
    std::vector<char> column;
    column.reserve(9);
    for(int i = 0; i < 9; i++){
        column.push_back(grid[i][c]);
    }
    for(char ch : column){
        if(ch == k){
            return false;
        }
    }
    return true;
}

bool search_box(std::vector<std::vector<char> > grid,int r, int c, char k){
    std::vector<char> box;
    box.reserve(9);
    for(int i = (r/3)*3; i < (r/3)*3+3; i++){
        for(int j = (c/3)*3; j < (c/3)*3+3; j++){
            box.push_back(grid[i][j]);
        }
    }

    for(char ch: box){
        if(ch == k){
            return false;
        }
    }
    return true;
}

bool is_valid(std::vector<std::vector<char> >grid, int r, int c, char k){
    bool not_in_row = search_row(grid,r,k);
    bool not_in_col = search_column(grid,c,k);
    bool not_in_box = search_box(grid,r,c,k);

    return not_in_row && not_in_col && not_in_box;
}

bool solve(std::vector<std::vector<char> >& grid,int r, int c){
    if(r == 9){
        return true;
    }else if(c == 9){
        return solve(grid, r+1,0);
    }else if(grid[r][c]!= '0'){
        return solve(grid, r, c+1);
    }else{
        for(int i = 0; i < 10; i++){
            char k[10 + sizeof(char)];
            std::sprintf(k, "%d", i);
            if(is_valid(grid,r,c,*k)){
                grid[r][c] = *k;
                if(solve(grid, r,c+1)){
                    return true;
                }
                grid[r][c] = '0';
            }
        }
        return false;
    }
}




int main(){
    std::array<char,81> sudoku = {'0','0','0','0','1','0','0','0','9','0','3','1','2','4','8','0','7','0','0','0','0','0','0','0','4','1','0','3','0','7','0','0','5','2','6','0','0','8','4','6','0','1','9','3','0','0','5','9','4','0','0','7','0','1','0','6','2','0','0','0','0','0','0','0','7','0','8','5','6','1','9','0','5','0','0','0','3','0','0','0','0',};

    std::vector<std::vector<char> > sudoku_vec_vec = sud_to_vec_vec(sudoku);

    std::cout << std::endl << "UNSOLVED: " << std::endl << std::endl;

    print_sudoku(sudoku_vec_vec);

    std::cout << std::endl << "SOLVED: " << std::endl << std::endl;

    std::cout << solve(sudoku_vec_vec,0,0) << std::endl;

    print_sudoku(sudoku_vec_vec);
}