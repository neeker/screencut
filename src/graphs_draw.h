#ifndef  GRAPHS_DRAW_H
#define  GRAPHS_DRAW_H

#include "windef.h"
#include "graphs_util.h"

namespace graphs {
  class IGraph {
  public:
    IGraph() {}
    virtual ~IGraph() {}

  public:
    virtual void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC) = 0;
  };

  class GraphRectangle: public IGraph {
  public:
    GraphRectangle() {}
    ~GraphRectangle() {}
  public:
    void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC);
  };

  class GraphEllipse: public IGraph {
  public:
    GraphEllipse() {}
    ~GraphEllipse() {}
  public:
    void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC);
  };

  class GraphArrowLine: public IGraph {
  public:
    GraphArrowLine() {}
    ~GraphArrowLine() {}
  public:
    void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC);
  };

  class GraphScrawl: public IGraph {
  public:
    GraphScrawl() {}
    ~GraphScrawl() {}
  public:
    void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC);
  };

  class GraphHighlight: public IGraph {
  public:
    GraphHighlight() {}
    ~GraphHighlight() {}
  public:
    void DrawGraph(HDC hDC, POINT ptStart, POINT ptEnd, int nPenWidth, COLORREF dwPenColor, const RectX& rcRgn = SCREEN_RC);
  };

  class GraphFactory {
  public:
    GraphFactory() {}
    virtual ~GraphFactory() {}
  public:
    static IGraph* CreateGraph(int graphID);
  };

}
#endif
