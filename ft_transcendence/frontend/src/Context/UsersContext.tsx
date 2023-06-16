import React, {
  createContext,
  useContext,
  useEffect,
  useState,
  useMemo,
  ReactNode,
} from "react";
import { WebSocketContext } from "./WebSocketContext";
import { User, useAuth } from "./AuthContext";

export const UsersContext = createContext<User[]>([]);

/**
 * The context provider for users. This component manages user data for the application.
 * @param {ReactNode} children - The child nodes for the UserProvider.
 * @returns {React.JSX.Element} The UsersContext Provider element that wraps around child elements.
 */
function UserProvider({
  children,
}: {
  children: ReactNode;
}): React.JSX.Element {
  const socket = useContext(WebSocketContext);
  const { user } = useAuth();
  const [userStore, setUserStore] = useState<User[]>([]);

  useEffect(() => {
    socket?.on("allusers", (users: User[]) => setUserStore(users));
    socket?.on("updateuser", (userId: string, userUpdated: User) => {
      console.log("updateuser", userId, userUpdated);
      setUserStore((store) =>
        store.map((user) =>
          user.id === userId ? {...user, ...userUpdated} : user
        )
      );
    });
    if (user) socket?.emit("allusers", user.id);
    return () => {
      socket?.off("allusers");
    };
  }, [socket, setUserStore, user]);

  const value = useMemo(() => userStore, [userStore]);

  return (
    <UsersContext.Provider value={value}>{children}</UsersContext.Provider>
  );
}

export default UserProvider;
