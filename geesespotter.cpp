#include "geesespotter_lib.h"
#include "geesespotter.h"


char *createBoard(std::size_t xdim, std::size_t ydim){
            char * board {new char[xdim*ydim]};
    for( std::size_t i = 0; i < xdim*ydim; i++){
        board[i]=0;
    }
    
    
    return board;
}
void cleanBoard(char *board){
    delete[] board;
    board=nullptr;
}
  void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(int rows{0};rows<ydim;rows++){
        for(int column{0};column<xdim;column++){
            if((board[column+xdim*rows]&markedBit())==markedBit()){
                std::cout<<"M";
            }
            else if((board[column+xdim*rows]&hiddenBit())==hiddenBit()){
                std::cout<<"*";
            }
            else{
                std::cout<<(board[column+xdim*rows]&valueMask());
                            }
        }
        std::cout<<std::endl;
    }
    

  }

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    for(int rows{0};rows<ydim;rows++){
        for(int column{0};column<xdim;column++){
            std::size_t num_geese{0};
            //if there's no goose in the field
            
            if((board[rows*xdim+column]&valueMask())!=9){
                //the field to the left has goose
               if((((rows*xdim+column)-1)>=0) && ((((board[rows*xdim+column-1])&valueMask())==9))&&(((rows*xdim+column)-1)>=(rows*xdim))&&((rows*xdim+column)-1)<((rows+1)*xdim)){
                num_geese++;
               }
               //the field to the right has goose
               if((((rows*xdim+column)+1)<=xdim*ydim)&& (((board[rows*xdim+column+1])&valueMask())==9)&&(((rows*xdim+column)+1)<((rows+1)*xdim))&&(((rows*xdim+column)-1)>=(rows*xdim))){
                num_geese++;
               }
               //the field above has goose
               if((((rows*xdim+column)-xdim)>=0) && ((((board[rows*xdim+column-xdim])&valueMask())==9))){
                num_geese++;
               }
               //the field below has goose
               if(((rows*xdim+column+xdim)<=(xdim*ydim)) && (((board[rows*xdim+column+xdim])&valueMask())==9)){
                num_geese++;
               }
               //the field to the top left has goose
               if((((rows*xdim+column)-xdim-1)<(xdim*ydim))&&(((rows*xdim+column)-xdim-1)>=0) && ((((board[rows*xdim+column-xdim-1]))&valueMask())==9)&&(((rows*xdim+column)-xdim-1)>=((rows-1)*xdim))&&((rows*xdim+column)-xdim-1)<(rows*xdim)){
                num_geese++;
               }
               //the field to the top right has goose
               if(((((rows*xdim+column)-xdim)+1)<=(xdim*ydim))&&((((rows*xdim+column)-xdim)+1)>=0) && (((board[rows*xdim+column-xdim+1])&valueMask())==9)&&((((rows*xdim+column)-xdim)+1)<(rows*xdim))&&(((rows*xdim+column)-xdim)+1)>=((rows-1)*xdim)){
                num_geese++;
               } 
               //the field to the bottom left has goose
               if(((rows*xdim+column+xdim-1)<=xdim*ydim) && (((board[rows*xdim+column+xdim-1])&valueMask())==9)&&(((rows*xdim+column)+xdim-1)>=((rows+1)*xdim))&&((rows*xdim+column)+xdim-1)<(rows+2)*xdim){
                num_geese++;
               }
               //the field to the bottom right has goose
               if((((rows*xdim+xdim+column)+1)<=(xdim*ydim)) && (((board[rows*xdim+column+xdim+1])&valueMask())==9)&&(((rows*xdim+column)+xdim+1)<(rows+2)*xdim)&&((rows*xdim+column)+xdim+1)>=((rows+1)*xdim)){
                num_geese++;
               }
               board[rows*xdim+column]=(board[rows*xdim+column]&valueMask());
                board[rows*xdim+column]|=num_geese;
            } 
            

           
        }

}
}


void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for(std::size_t i = 0; i < xdim*ydim;i++){
        
        board[i] |= hiddenBit();
        }
    }


int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    if((board[yloc*xdim+xloc]& markedBit())==markedBit()){
        return 1;
    }
    else if((board[yloc*xdim+xloc] & hiddenBit())!=hiddenBit()) {
        return 2;
   }
   else if((board[yloc*xdim+xloc]& valueMask()==9)){                      
    board[yloc*xdim+xloc]|=9;
    return 9;
   }
   else{

   if((board[yloc*xdim+xloc])& valueMask()==0){
    board[yloc*xdim+xloc]&=(~hiddenBit());
         //the field to the left has goose
               if((((yloc*xdim+xloc)-1)>=0) && (((yloc*xdim+xloc)-1)>=(yloc*xdim))&&((yloc*xdim+xloc)-1)<((yloc+1)*xdim)){
                 board[yloc*xdim+xloc-1]&=(~hiddenBit());
               }
               //the field to the right has goose
               if((((yloc*xdim+xloc)+1)<=xdim*ydim)&&(((yloc*xdim+xloc)+1)<(yloc*xdim+xdim))){
                board[yloc*xdim+xloc+1]&=(~hiddenBit());
               }
               //the field above has goose
               if((((yloc*xdim+xloc)+1)<=xdim*ydim)&& (((yloc*xdim+xloc)+1)<((yloc+1)*xdim))&&(((yloc*xdim+xloc)-1)>=(yloc*xdim))){
                 board[yloc*xdim+xloc-xdim]&=(~hiddenBit());
               }
               //the field below has goose
               if(((yloc*xdim+xloc+xdim)<=(xdim*ydim))){
                 board[yloc*xdim+xloc+xdim]&=(~hiddenBit());
               }
               //the field to the top left has goose
               if((((yloc*xdim+xloc)-xdim-1)<(xdim*ydim))&&(((yloc*xdim+xloc)-xdim-1)>=0) && (((yloc*xdim+xloc)-xdim-1)>=((yloc-1)*xdim))&&((yloc*xdim+xloc)-xdim-1)<(yloc*xdim)){
                 board[yloc*xdim+xloc-xdim-1]&=(~hiddenBit());
               }
               //the field to the top right has goose
               if(((((yloc*xdim+xloc)-xdim)+1)<=(xdim*ydim))&&((((yloc*xdim+xloc)-xdim)+1)>=0) &&((((yloc*xdim+xloc)-xdim)+1)<(yloc*xdim))&&(((yloc*xdim+xloc)-xdim)+1)>=((yloc-1)*xdim)){
                 board[yloc*xdim+xloc-xdim+1]&=(~hiddenBit());
               } 
               //the field to the bottom left has goose
               if(((yloc*xdim+xloc+xdim-1)<=xdim*ydim) &&(((yloc*xdim+xloc)+xdim-1)>=((yloc+1)*xdim))&&((yloc*xdim+xloc)+xdim-1)<(yloc+2)*xdim){
                board[yloc*xdim+xloc+xdim-1]&=(~hiddenBit());
               }
               //the field to the bottom right has goose
               if((((yloc*xdim+xdim+xloc)+1)<=(xdim*ydim)) &&(((yloc*xdim+xloc)+xdim+1)<(yloc+2)*xdim)&&((yloc*xdim+xloc)+xdim+1)>=((yloc+1)*xdim)){
                 board[yloc*xdim+xloc+xdim+1]&=(~hiddenBit());
               }

           

   }
   else{
    board[yloc*xdim+xloc]&=(~hiddenBit());
   }
   }


return 0;
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
   
    if((board[yloc*xdim+xloc] & hiddenBit())!=hiddenBit()) {
        return 2;
   }
   else{
         board[yloc*xdim+xloc]^=markedBit();
    
    }
    return 0;
    }

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    int num_win{0};
    int num_lose{0};
    for(int i{0};i<xdim*ydim;i++){
        if(((board[i]&hiddenBit())==0)&& ((board[i]& valueMask())!=9)){
            num_win++;
        }
        else if((board[i]& valueMask())==9){
            num_lose++;
        }
    }
    if(num_win==((xdim*ydim)-num_lose)){
           return true;
        }
        else{
            return false; 
        }
}