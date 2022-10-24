#include <App.hh>
#include <MainFrame.hh>
#include <GameBoardPanel.hh>
#include <Board.hh>
#include <stdio.h>
#include <MiniMax.hh>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

GameBoardPanel::GameBoardPanel(wxFrame* parent) :
wxPanel(parent), myBoard(Board(3,3))
{
  Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
  Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseLeftClick, this);
}

GameBoardPanel::GameBoardPanel(wxFrame* parent, Board board) :
    wxPanel(parent), myBoard(board), scorePlayer1(0), scorePlayer2(0)
{
    Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
    Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseLeftClick2, this);
    Bind(wxEVT_MOTION, &GameBoardPanel::OnMouseMove, this);
}


void GameBoardPanel::paintEvent(wxPaintEvent & evt){
  wxPaintDC dc(this);
  renderGame(dc);
  //render(dc);
}

void GameBoardPanel::paintNow() {
  wxClientDC dc(this);
  renderGame(dc);
  //render(dc);
}

void GameBoardPanel::render(wxDC& dc) {
  myBoard.getScoreP1();
  wxSize size = this->GetSize();
  dc.SetPen(*wxBLACK_PEN);
  int nrows = 10;
  int ncolumns = 10;
  double widthSize = size.x / (ncolumns+1);
	double heightSize = size.y / (nrows+1);
  double rowStartPosition = 27.0;
  for (int i = 0; i < ncolumns + 1; i++) {
    double columStartPosition = 27.0;
    for (int j = 0; j < nrows + 1; j++) {
      dc.SetBrush(*wxBLACK_BRUSH);
      dc.DrawCircle(rowStartPosition, columStartPosition ,5);
      dc.SetBrush(*wxWHITE_BRUSH);
      if (!(j == nrows)) {
        dc.DrawRectangle(rowStartPosition-5, columStartPosition + 5, 10, (rowStartPosition+widthSize+2)-rowStartPosition);
      }
      if (!(i==ncolumns)) {
        dc.DrawRectangle(rowStartPosition+5, columStartPosition - 5, (columStartPosition+heightSize-2)-columStartPosition, 10);
      }
      columStartPosition += heightSize;
    }
    rowStartPosition += widthSize;
  }
}


void GameBoardPanel::renderGame(wxDC& dc){
    wxSize size = this->GetSize();
    dc.SetPen(*wxBLACK_PEN);
    int nrows = myBoard.getBoardRowSize();
    int ncolumns = myBoard.getBoardColSize();

    double xMargin = 27; 
    double yMargin = 27; 

    double boardWidth = size.x - 2*xMargin; 
    double boardHeight = size.y - 2*yMargin;

    double cellWidth = boardWidth / ncolumns; 
    double cellHeight = boardHeight / nrows;

    double columnStartPosition = xMargin;
    for (int i = 0; i < ncolumns + 1; i++) {
      double rowStartPosition = yMargin;
      for (int j = 0; j < nrows + 1; j++) {       
        Cell* celda = myBoard.getCell(j, i);
            if (i < ncolumns && j < nrows) {
               // Dibujar línea de la derecha de las cajas
              if (celda->east == PLAYER1){
                dc.SetBrush(*wxBLUE_BRUSH);
                dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 5, cellHeight);
              } else {
                    if (celda->east == PLAYER2) {
                      dc.SetBrush(*wxRED_BRUSH);
                      dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 5, cellHeight);
                    }
                }  
              // Dibujar línea de la izquieda de las cajas
              if (celda->west == PLAYER1){
                dc.SetBrush(*wxBLUE_BRUSH);
                dc.DrawRectangle((columnStartPosition - 2), rowStartPosition, 5, cellHeight);
              } else {
                    if (celda->west == PLAYER2) {
                      dc.SetBrush(*wxRED_BRUSH);
                      dc.DrawRectangle((columnStartPosition - 2), rowStartPosition, 5, cellHeight);
                    }
                } 
              // Dibujar línea superior 
               if (celda -> north == PLAYER1) {
                    dc.SetBrush(*wxBLUE_BRUSH);
                    dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition-2), cellWidth, 5);
                }
                else {
                    if (celda->north == PLAYER2) {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition-2), cellWidth, 5);
                    }
                }
            // Dibujar línea inferior 
            if (celda -> south == PLAYER1) {
                    dc.SetBrush(*wxBLUE_BRUSH);
                    dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition + cellHeight - 2), cellWidth, 5);
                }
                else {
                    if (celda -> south == PLAYER2) {
                        dc.SetBrush(*wxRED_BRUSH);
                        dc.DrawRectangle((columnStartPosition - 2), (rowStartPosition+ cellHeight - 2), cellWidth, 5);
                    }
                }
          }
        dc.SetBrush(*wxBLACK_BRUSH);
        //Dibujar el circulo
        dc.DrawCircle(columnStartPosition, rowStartPosition, 5);
        rowStartPosition += cellHeight;
      }
        columnStartPosition +=  cellWidth;
    }
}

void GameBoardPanel::drawTemporalLine(wxDC& dc, int rowIndex, int columIndex, Directions direction, double cellWidth, double cellHeight){
    double xMargin = 27; 
    double yMargin = 27; 
    switch (direction) {
      dc.SetBrush(*wxWHITE_BRUSH);
    case WEST:
        dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), 5, cellHeight);    
      break;
    case EAST:
        //dc.DrawRectangle((columnStartPosition + cellWidth - 2), rowStartPosition, 7, cellHeight);
        dc.DrawRectangle((xMargin + (columIndex + 1) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), 5, cellHeight);
      break;
    case NORTH:
      dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + rowIndex*cellHeight - 2), cellWidth, 5);
      break;
    case SOUTH:
      dc.DrawRectangle((xMargin + (columIndex) * (cellWidth) - 2), (yMargin + (rowIndex + 1)*cellHeight - 2), cellWidth, 5);
      break;
    default:
      break;
    }
}

Movement GameBoardPanel::getTemporalMovement(double xMousePosition, double yMousePosition){
  double xMargin = 27; 
  double yMargin = 27; 

  wxSize size = this->GetSize();

  int nrows = myBoard.getBoardRowSize(); //TODO
  int ncolumns = myBoard.getBoardColSize(); //TODO

  double boardWidth = size.x - 2*xMargin; 
  double boardHeight = size.y - 2*yMargin;

  double cellWidth = boardWidth / ncolumns; 
  double cellHeight = boardHeight / nrows;
  //Para obtener la posición X (columna) en board.
  double xPosition = (xMousePosition - xMargin) / cellWidth;
    //Para obtener la posición Y (fila) en board.
  double yPosition = (yMousePosition - yMargin) / cellHeight;

  int columnIndex = int(xPosition);
  int rowIndex = int(yPosition);

  columnIndex = std::min(ncolumns-1, columnIndex);
  rowIndex = std::min(nrows - 1, rowIndex);

  double columnStartPosition = xMargin;
  double rowStartPosition = yMargin;

  return Movement(rowIndex, columnIndex, getDirection(xPosition, yPosition, columnIndex, rowIndex));
}

Directions GameBoardPanel::getDirection(double xPosition, double yPosition, int columnIndex, int rowIndex){
  double fromXstart = xPosition - columnIndex; 
  double fromYstart = yPosition - rowIndex; 
  // Usamos como "margen" de las líneas 0.2 
  if(fromYstart < 0.2 && fromYstart > -0.2 && fromXstart > 0.1 && fromXstart < 0.9){
    return NORTH; 
  } 

  if(fromYstart < 1.2 && fromYstart > 0.8 && fromXstart > 0.1 && fromXstart < 0.9){
    return SOUTH;
  }

  if(fromYstart > 0.1 && fromYstart < 0.9 && fromXstart > -0.2 && fromXstart < 0.2){
    return WEST;
  }
  
  if(fromYstart > 0.1 && fromYstart < 0.9 && fromXstart > 0.8 && fromXstart < 1.2){
    return EAST;
  }

  return EMPTY;
}

/*
void GameBoardPanel::OnMouseLeftClick2(wxMouseEvent& evt) {
    wxPoint position = evt.GetPosition();
    Movement move = getTemporalMovement(position.x, position.y);
    if (move.isValid(&myBoard)){
      move.playAndAssignOwner(myBoard, PLAYER2);
      myBoard.scoreUpdater();
      int auxiliarScorePlayer2 = myBoard.getScoreP2();

      if(auxiliarScorePlayer2 > scorePlayer2){
        scorePlayer2 = auxiliarScorePlayer2;
      } else {
        int auxiliarScorePlayer1; 
        do
        {
          auxiliarScorePlayer1 = scorePlayer1;
          MiniMax minimax = {myBoard, true, 4};
          minimax.performAlfaBeta(true, -1500, 1500);
          minimax.getBestMove().playAndAssignOwner(myBoard, PLAYER1);
          minimax.~MiniMax();
          myBoard.scoreUpdater();
          scorePlayer1 = myBoard.getScoreP1();
        } while (scorePlayer1 > auxiliarScorePlayer1);       
      }
    }
  wxString message = wxString::Format("PLAYER1:%d, PLAYER2:%d", scorePlayer1, scorePlayer2);
 	wxLogStatus(message);
    Refresh();
}

*/

void GameBoardPanel::OnMouseLeftClick2(wxMouseEvent& evt) {
    wxPoint position = evt.GetPosition();
    Movement move = getTemporalMovement(position.x, position.y);
    if (move.isValid(&myBoard)){
      move.playAndAssignOwner(myBoard, PLAYER1);
      myBoard.scoreUpdater();
      int auxiliarScorePlayer1 = myBoard.getScoreP1();

      if(auxiliarScorePlayer1 > scorePlayer1){
        scorePlayer1 = auxiliarScorePlayer1;
      } else {
        int auxiliarScorePlayer2; 
        do
        {
          auxiliarScorePlayer2 = scorePlayer2;
          MiniMax minimax = {myBoard, false, 4};
          minimax.performAlfaBeta(true, -15000, 15000);
          minimax.getBestMove().playAndAssignOwner(myBoard, PLAYER2);
          minimax.~MiniMax();
          myBoard.scoreUpdater();
          scorePlayer2 = myBoard.getScoreP2();
        } while (scorePlayer2 > auxiliarScorePlayer2);       
      }
    }
  wxString message = wxString::Format("PLAYER1:%d, PLAYER2:%d", scorePlayer1, scorePlayer2);
 	wxLogStatus(message);
  Refresh();
}

void GameBoardPanel::OnMouseLeftClick3(wxMouseEvent& evt){
  wxPoint position = evt.GetPosition();
  Movement move = getTemporalMovement(position.x, position.y);
  if (move.isValid(&myBoard)){
      move.playAndAssignOwner(myBoard, PLAYER1);
      myBoard.scoreUpdater();
      int newScore = myBoard.getScoreP1();
      if(newScore > scorePlayer1){
        scorePlayer1 = newScore;  
      } else {
        Unbind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseLeftClick, this);
      }
  }
}


void GameBoardPanel::OnMouseLeftClick(wxMouseEvent& evt) {
  // Para obtener la posici�n del mouse. 
	wxPoint position = evt.GetPosition();
	//wxString message = wxString::Format("Left mouse click (x=%d, y=%d)", position.x, position.y);
  Movement move = getTemporalMovement(position.x, position.y);
  
  if (move.isValid(&myBoard)){
    int newScore;
    if (gameTurn == 1) {
      move.playAndAssignOwner(myBoard, PLAYER1);
      myBoard.scoreUpdater();
      newScore = myBoard.getScoreP1();
      if(newScore > scorePlayer1){
        scorePlayer1 = newScore;
        gameTurn *= -1;
      }
    } else {
      move.playAndAssignOwner(myBoard, PLAYER2);
      myBoard.scoreUpdater();
      newScore = myBoard.getScoreP2();
      if(newScore > scorePlayer2){
        scorePlayer2 = newScore;
        gameTurn *= -1;
      }
    }
    gameTurn *= -1;
  }

  Refresh();

  wxString message = wxString::Format("Left mouse click (row=%d, column=%d, direction=%d)", move.getXPos(), move.getYPos(), move.getLineDirection());
 	wxLogStatus(message);
}

void GameBoardPanel::OnMouseMove(wxMouseEvent& evt) {
    wxClientDC dc(this);
    wxPoint position = evt.GetPosition();
    //Refresh();
    Movement move = getTemporalMovement(position.x, position.y);
    if (move.isValid(&myBoard)){
      double xMargin = 27;
      double yMargin = 27;
      wxSize size = this->GetSize();

      int nrows = myBoard.getBoardRowSize(); //TODO
      int ncolumns = myBoard.getBoardColSize(); //TODO

      double boardWidth = size.x - 2*xMargin; 
      double boardHeight = size.y - 2*yMargin;

      double cellWidth = boardWidth / ncolumns; 
      double cellHeight = boardHeight / nrows;

      drawTemporalLine(dc, move.getXPos(), move.getYPos(), move.getLineDirection(), cellWidth, cellHeight);
  }

  renderGame(dc);

}


bool GameBoardPanel::ZoneClicked(wxEvent& evt) {
  return true;
}