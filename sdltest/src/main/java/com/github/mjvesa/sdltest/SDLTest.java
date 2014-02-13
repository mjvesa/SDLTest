package com.github.mjvesa.sdltest;

import com.github.mjvesa.sdltest.client.SDLTestServerRpc;
import com.github.mjvesa.sdltest.client.SDLTestState;

import com.vaadin.annotations.JavaScript;

// This is the server-side UI component that provides public API 
// for SDLTest
@JavaScript({ "sdltest.js" })
public class SDLTest extends com.vaadin.ui.AbstractComponent {

    // To process events from the client, we implement ServerRpc
    private SDLTestServerRpc rpc = new SDLTestServerRpc() {
    };

    public SDLTest() {

        // To receive events from the client, we register ServerRpc
        registerRpc(rpc);
    }

    // We must override getState() to cast the state to SDLTestState
    @Override
    public SDLTestState getState() {
        return (SDLTestState) super.getState();
    }
}
