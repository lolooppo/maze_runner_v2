#include "maze.h"
// up down left right
//this for walls directions
int dx_cell[4] = {-2, +0, +0, +2};
int dy_cell[4] = {+0, +2, -2, +0};

//this for valid cells
int dx_wall[4] = {-1, +0, +0, +1};
int dy_wall[4] = {+0, +1, -1, +0};



//size of the maze(varying based on the player chosen level)
int N{20};


//the 2d character array represents the maze.
char arr[41][41]{' '};
bool visited[41][41]{0};




//check if the given row and column valid or not
bool valid(int r, int c){
    return r>-1 and r<2*N+1 and c>-1 and c<2*N+1;
}


/*
- Used only 1 time.
- You can replace it in the generate maze function.
*/
//takes a random node and returns its row and column.
std::pair<int, int>get_row_column(int &node){
    int r = (node+N-1)/N;
    int c = node-(r-1)*N;

    return{r+r, c+c};
}


void print_maze(){
    for(int i=0; i<2*N+1; i++){
        for(int j=0; j<2*N+1; j++)
            std::cout<<arr[i][j];
        std::cout<<'\n';
    }
}

//initialize the maze with spaces.
void initialize_maze(){
    for(int i=0; i<2*N+1; i++){
        for(int j=0; j<2*N+1; j++){
            if(i%2 == 0){
                arr[i][j] = '-';
            }else{
                arr[i][j] = j%2? ' ' : '!';
            }
        }
    }
}

/*
- Here I used a randomized depth first search algorithm.
- I used the iterative way to optimize the memory usage.
*/
void generate_maze(){

    initialize_maze();

    std::stack<std::pair<int, int>> st;

    srand(time(0));

    //the initial node to start the algorithm with.
    int node = rand() % (N*N) + 1;
    std::pair<int, int> rc = get_row_column(node);
    rc.first--, rc.second--;    //Just to be zero base.

    visited[rc.first][rc.second] = true;
    st.push(rc);

    while(!st.empty()){
        std::pair<int, int> curr = st.top();

        //to store the indexes of the unvisited neighbors of the current node.
        std::vector<int> neighbors;

        for(int i=0; i<4; i++){
            int new_r = curr.first, new_c = curr.second;
            new_r += dx_cell[i];
            new_c += dy_cell[i];

            if(valid(new_r, new_c) and !visited[new_r][new_c]){
                neighbors.push_back(i);
            }
        }

        //if the node has no unvisited valid neighbors, then pop the current node from the stack,
        //otherwise let it and push a randomly selected neighbor.
        if((int)neighbors.size() == 0){
            st.pop();
            continue;
        }


        //chose a random neighbor
        int idx = rand() % neighbors.size();
        int dir = neighbors[idx];

        int cell_r = curr.first, cell_c = curr.second;
        int wall_r = curr.first, wall_c = curr.second;

        cell_r+=dx_cell[dir], cell_c+=dy_cell[dir];
        wall_r+=dx_wall[dir], wall_c+=dy_wall[dir];



        visited[cell_r][cell_c] = true;
        arr[wall_r][wall_c] = ' ';

        std::pair<int, int> node = {cell_r, cell_c};
        st.push(node);
    }
}
