import React, { createContext, useCallback, useContext, useEffect, useMemo, useState } from 'react';

export enum UserStatus {
  OFFLINE,
  ONLINE,
  PLAYING,
}

export interface User {
  id: string;
  avatar?: string;
  username: string;
  login:string;
  isFriend: boolean;
  isBanned: boolean;
  hasBanned: boolean;
  friendshipRequestSent: boolean;
  friendshipRequestReceived: true;
  email: string;
  blocked: string[];
  friends: string[];
  friendRequest: string[];
  status: UserStatus;
  twoFactorAuthEnabled: boolean;
  twoFactorAuthSecret:string;
  authEnable: boolean;
  matches: any[];
  matchesPlayed: number;
  matchesWon: number;
  matchesLost: number;
  messagesReceived: number;
  messagesSent: number;
  logTimeInMinutes: number;
  level: number;
}

export interface AuthContextData {
  accessToken: string | null;
  setAccessToken: (token: string | null) => void;
  user: User | null;
  setUser: (user: User | null) => void;
  clearAccessToken: () => void;
  logout: () => void;
  updateCurrentUser: (token: string) => void;
}

export const AuthContext = createContext<AuthContextData>({} as AuthContextData);
export const useAuth = () => useContext(AuthContext);

export const AuthProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [accessToken, setAccessToken] = useState<string | null>(() => {
    const storedToken = sessionStorage.getItem('accessToken');
    return storedToken ?? null;
  });
  const [user, setUser] = useState<User | null>(null);
  const hostname = useMemo(() => window.location.hostname, []);

  const clearCookie = useCallback(() => {
    document.cookie = 'Authentication=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
  }, []);

  const clearAccessToken = useCallback(() => {
    sessionStorage.removeItem('accessToken');
    setAccessToken(null);
  }, []);

  const updateCurrentUser = useCallback(async (token: string) => {
    try {
      const response = await fetch(`http://${hostname}:3000/auth/me?token=${token}`);
      if (response.ok) {
        const userData = await response.json();
        setUser(userData);
      } else {
        throw new Error('Something went wrong. Could not find the user.');
      }
    } catch (error) {
      throw new Error('Something went wrong. Could not find the user.');
    }
  }, [hostname]);

  const logout = useCallback(() => {
    sessionStorage.removeItem('accessToken');
    localStorage.removeItem('qrCode');
    localStorage.removeItem('enable');
    document.cookie = 'Authentication=; path=/;';
    setAccessToken(null);
    setUser(null);
    fetch(`http://localhost:${process.env.REACT_APP_PORT}/auth/logout`, {
      method: 'GET',
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${accessToken}`,
      },
      credentials: 'include',
    })
    .then(() => {
      window.location.href = `http://localhost:${process.env.REACT_APP_PORT}/auth`;
    })
    .catch((error) => {});
  }, [accessToken]);

  useEffect(() => {
    const storedToken = sessionStorage.getItem('accessToken');
    const cookies = document.cookie.split(';');
    let token = null;

    for (const element of cookies) {
      const cookie = element.trim();
      if (cookie.startsWith('Authentication=')) {
        token = cookie.split('=')[1];
        break;
      }
    }

    if (token) {
      setAccessToken(token);
      sessionStorage.setItem('accessToken', token);
      clearCookie();
    } else if (storedToken) {
      setAccessToken(storedToken);
    }
  }, [clearCookie]);

  useEffect(() => {
    if (accessToken) {
      updateCurrentUser(accessToken)
        .catch((error) => {
        });
    }
  }, [accessToken, setUser, updateCurrentUser]);

  useEffect(() => {
    if (user) {
      const logTimeInMinutesInterval = setInterval(() => {
        setUser((user) => {
          if (user) {
            return { ...user, logTimeInMinutes: 1 + user.logTimeInMinutes };
          }
          return user;
        });
      }, 60000);
      return () => clearInterval(logTimeInMinutesInterval);
    }
  }, [user]);

  const value = useMemo(() => ({
    accessToken,
    setAccessToken,
    user,
    setUser,
    clearAccessToken,
    logout,
    updateCurrentUser
  }), [accessToken, setAccessToken, user, setUser, clearAccessToken, logout, updateCurrentUser]);


  return (
    <AuthContext.Provider value={value}>
      {children}
    </AuthContext.Provider>
  );
};
