#include <App.hh>
#include <MainFrame.hh>
#include <GameBoardPanel.hh>
#include <Board.hh>
#include <stdio.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

GameBoardPanel::GameBoardPanel(wxFrame* parent) :
wxPanel(parent), myBoard(Board(3,3))
{
  Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
  Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseEvent, this);
}

GameBoardPanel::GameBoardPanel(wxFrame* parent, Board board) :
    wxPanel(parent), myBoard(board)
{
    Bind(wxEVT_PAINT, &GameBoardPanel::paintEvent, this);
    Bind(wxEVT_LEFT_DOWN, &GameBoardPanel::OnMouseEvent, this);
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

void GameBoardPanel::OnMouseEvent(wxMouseEvent& evt) {
  // Para obtener la posici�n del mouse. 
	wxPoint position = evt.GetPosition();
	//wxString message = wxString::Format("Left mouse click (x=%d, y=%d)", position.x, position.y);
  Movement move = getTemporalMovement(position.x, position.y);
  wxString message = wxString::Format("Left mouse click (row=%d, column=%d, direction=%d)", move.getXPos(), move.getYPos(), move.getLineDirection());
 	wxLogStatus(message);
  Refresh();
  
}

bool GameBoardPanel::ZoneClicked(wxEvent& evt) {
  return true;
}