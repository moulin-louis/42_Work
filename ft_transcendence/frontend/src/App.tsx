import "./App.css";
import React from "react";
import { Routes, Route } from "react-router-dom";
import ErrorPage from "./Pages/ErrorPage/ErrorPage";
import History from "./Pages/History/History";
import Auth from "./Pages/Auth/Auth";
import Dashboard from "./Pages/Dashboard/Dashboard";
import Friends from "./Pages/Friends/Friends";
import Play from "./Pages/Game/Game";
import Achievements from "./Pages/Achievements/Achievements";
import Help from "./Pages/Help/Help";
import PingPong from "./Pages/PingPong/PingPong"

import WebSocketProvider from "./Context/WebSocketContext";
import MessagesProvider from "./Context/ChatContext";
import { AuthProvider, useAuth } from "./Context/AuthContext";
import ChatContainer from "./Pages/Chat/ChatContainer";
import UnreadProvider from "./Context/UnreadContext";
import ChannelProvider from "./Context/ChannelContext";
import Settings from "./Pages/Settings/Settings";
import UserProvider from "./Context/UsersContext";
import SigninTwoFactor from "./Pages/Auth/SigninTwoFactor";
import CurrentUserProfile from "./Pages/Profile/CurrentUserProfile";

function AppRoutes() {
  const { accessToken } = useAuth();
  return (
    <Routes>
      <Route path="*" element={<ErrorPage />} />
      <Route path="/" element={!accessToken ? <Auth /> : <Dashboard />} />
      <Route path="/auth" element={<Auth />} />
      <Route
        path="/chat"
        element={!accessToken ? <Auth /> : <ChatContainer />}
      />
      <Route path="/friends" element={!accessToken ? <Auth /> : <Friends />} />
      <Route path="/history" element={!accessToken ? <Auth /> : <History />} />
      <Route path="/play" element={!accessToken ? <Auth /> : <Play />} />
      <Route path="/help" element={!accessToken ? <Auth /> : <Help />} />
      <Route path="/profile" element={!accessToken ? <Auth /> : <CurrentUserProfile /> } />

      <Route
        path="/achievements"
        element={!accessToken ? <Auth /> : <Achievements />}
      />
      <Route
        path="/settings"
        element={!accessToken ? <Auth /> : <Settings />}
      />
      <Route
        path="/2fa"
        element={<SigninTwoFactor />}
      />
      <Route
        path="/pingpong"
        element={!accessToken ? <Auth /> : <PingPong />} 
      />
    </Routes>
  );
}

function App() {
  return (
    <AuthProvider>
      <WebSocketProvider>
        <UserProvider>
          <MessagesProvider>
            <ChannelProvider>
              <UnreadProvider>
                <AppRoutes />
              </UnreadProvider>
            </ChannelProvider>
          </MessagesProvider>
        </UserProvider>
      </WebSocketProvider>
    </AuthProvider>
  );
}

export default App;
