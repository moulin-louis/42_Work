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
  authEnable: boolean;
  matches: any[];
  matchesPlayed: number;
  matchesWon: number;
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
  updateCurrentUser: (token: string) => Promise<User>;
}

export const AuthContext = createContext<AuthContextData>({} as AuthContextData);
export const useAuth = () => useContext(AuthContext);

export const AuthProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [accessToken, setAccessToken] = useState<string | null>(() => {
    const storedToken = sessionStorage.getItem('accessToken');
    return storedToken || null;
  });
  const [user, setUser] = useState<User | null>(null);
  const hostname = useMemo(() => window.location.hostname, []);

  const clearCookie = () => {
    document.cookie = 'Authentication=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
  };

  const clearAccessToken = () => {
    sessionStorage.removeItem('accessToken');
    setAccessToken(null);
  };

  const updateCurrentUser = useCallback(async (token: string): Promise<User> => {
    try {
      const response = await fetch(`http://${hostname}:3000/auth/me?token=${token}`);
      if (response.ok) {
        const userData = await response.json();
        return userData as User;
      } else {
        throw new Error('Something went wrong. Could not find the user.');
      }
    } catch (error) {
      throw new Error('Something went wrong. Could not find the user.');
    }
  }, [hostname]);

  const logout = async () => {
    try {
      await fetch('http://localhost:3000/auth/logout', {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
          Authorization: `Bearer ${accessToken}`,
        },
        credentials: 'include',
      });

      sessionStorage.removeItem('accessToken');
      localStorage.removeItem('qrCode');
      localStorage.removeItem('enable');
      document.cookie = 'Authentication=; path=/;';

      setAccessToken(null);
      setUser(null);
    } catch (error) {
      console.error('Logout error:', error);
    }
  };

  useEffect(() => {
    console.log(document.cookie);
    const storedToken = sessionStorage.getItem('accessToken');
    const cookies = document.cookie.split(';');
    let token = null;

    for (const element of cookies) {
      console.log("split cookie");
      const cookie = element.trim();
      if (cookie.startsWith('Authentication=')) {
        token = cookie.split('=')[1];
        console.log("size ", token.length);
        console.log(token);
        break;
      }
    }

    if (token) {
      console.log(token?.length);
      console.log("enter");
      setAccessToken(token);
      sessionStorage.setItem('accessToken', token);
      clearCookie();
    } else if (storedToken) {
      setAccessToken(storedToken);
    }
  }, []);

  useEffect(() => {
    console.log("access token  ",accessToken);
    if (accessToken) {
      console.log('second useEffect');
      updateCurrentUser(accessToken)
        .then((userData: User) => {
          console.log('userData', userData);
          setUser(userData);
        })
        .catch((error) => {
          console.error(error);
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

  return (
    <AuthContext.Provider value={{ accessToken, setAccessToken, user, setUser, clearAccessToken, logout, updateCurrentUser }}>
      {children}
    </AuthContext.Provider>
  );
};
