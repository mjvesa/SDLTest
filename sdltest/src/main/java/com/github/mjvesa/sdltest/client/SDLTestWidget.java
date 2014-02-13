package com.github.mjvesa.sdltest.client;

import com.google.gwt.dom.client.Document;
import com.google.gwt.dom.client.Element;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.ui.Widget;

public class SDLTestWidget extends Widget {
    
    private Timer timer;
    private int t;

    public SDLTestWidget() {

        Element root = Document.get().createDivElement();
        setElement(root);
        setStyleName("sdltest");
        setHeight("100%");
        setWidth("100%");
        Element renderCanvas = Document.get().createElement("canvas");
        root.appendChild(renderCanvas);
        renderCanvas.setId("canvas");
        renderCanvas.setClassName("emscripten");
        renderCanvas.setAttribute("width", "100%");
        renderCanvas.setAttribute("height", "100%");
        setCanvas(renderCanvas);
        
        initSDL();
        
        t = 0;
        timer = new Timer() {

            @Override
            public void run() {
                t++;
                drawFrame(t);
            }
        };
        
        timer.scheduleRepeating(1000 / 50);
    }

    private native void setCanvas(Element renderCanvas) /*-{
        $wnd.Module['canvas'] = renderCanvas;
    }-*/;

    private native void initSDL() /*-{
        var f = $wnd.Module.cwrap('init', 'void', []);
        f();
    }-*/;

    private native void drawFrame(int t) /*-{
        var f = $wnd.Module.cwrap('drawframe', 'number', []);
        f(t);
    }-*/;

}