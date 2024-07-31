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
bool valid(int x, int y){
    return x>-1 and x<2*N+1 and y>-1 and y<2*N+1;
}


/*
- Used only 1 time.
- You can replace it in the generate maze function.
*/
//takes a random node and returns its row and column.
std::pair<int, int>get_row_column(int &node){
    int x = (node+N-1)/N;
    int y = node-(x-1)*N;

    return{x+x, y+y};
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
    std::pair<int, int> xy = get_row_column(node);
    xy.first--, xy.second--;    //Just to be zero base.

    visited[xy.first][xy.second] = true;
    st.push(xy);

    while(!st.empty()){
        std::pair<int, int> curr = st.top();

        //to store the indexes of the unvisited neighbors of the current node.
        std::vector<int> neighbors;

        for(int i=0; i<4; i++){
            int new_x = curr.first, new_y = curr.second;
            new_x += dx_cell[i];
            new_y += dy_cell[i];

            if(valid(new_x, new_y) and !visited[new_x][new_y]){
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

        int cell_x = curr.first, cell_y = curr.second;
        int wall_x = curr.first, wall_y = curr.second;

        cell_x+=dx_cell[dir], cell_y+=dy_cell[dir];
        wall_x+=dx_wall[dir], wall_y+=dy_wall[dir];



        visited[cell_x][cell_y] = true;
        arr[wall_x][wall_y] = ' ';

        std::pair<int, int> node = {cell_x, cell_y};
        st.push(node);
    }
}


//(Backtrack Depth First Search)for solving the maze
std::vector<std::pair<int, int>> path;
bool dfs(int x, int y){
    //check if we reached the target point
    if(x==1 and y==39){
        path.push_back({x,y});
        return true;
    }

    visited[x][y] = true;
    path.push_back({x,y});

    for(int i=0; i<4; i++){
        if(valid(x+dx_wall[i], y+dy_wall[i]) and arr[x+dx_wall[i]][y+dy_wall[i]]==' ' and !visited[x+dx_wall[i]][y+dy_wall[i]]){
            if(dfs(x+dx_wall[i], y+dy_wall[i]))
                return true;
        }
    }

    //backtrack
    path.pop_back();
    return false;
}
void solve_maze(){
    memset(visited, false, sizeof(visited));
    dfs(39, 1);
    for(auto &p:path){
        arr[p.first][p.second] = 'S';
    }
}
