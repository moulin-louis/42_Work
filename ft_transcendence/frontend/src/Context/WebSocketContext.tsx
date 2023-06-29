import { createContext, useEffect, useState, useMemo, ReactNode } from "react";
import { io, Socket } from "socket.io-client";
import { useAuth } from "./AuthContext";
import { toast, ToastContainer } from "react-toastify";
import 'react-toastify/dist/ReactToastify.css';

export const WebSocketContext = createContext<Socket | undefined>(undefined);

enum NotificationType {
  Info,
  Success,
  Warning,
  Error,
}

interface Notification {
  type: NotificationType;
  message: string;
}

/**
 * WebSocketProvider component is responsible for creating and managing the WebSocket connection.
 * @param {ReactNode} props.children - The child components of this provider.
 * @returns {React.JSX.Element} The WebSocketProvider component rendering its child components and a toast container for notifications.
 */
function WebSocketProvider({
  children,
}: {
  children: ReactNode;
}): React.JSX.Element {
  const { accessToken, user } = useAuth();
  const [socket, setSocket] = useState<Socket | undefined>(undefined);

  useEffect(() => {
    if (user?.id && accessToken) {
      const socketIOClient = io(`http://localhost:3000`, {
        query: { userId: user?.id, token: accessToken },
      });
      setSocket(socketIOClient);

      socketIOClient.on("connect", () => {
        socketIOClient.emit("saveusersocket", user?.id);
      });

      socketIOClient.on("notification", (notification: Notification) => {
        const notificationFunctions = {
          [NotificationType.Info]: toast.info,
          [NotificationType.Success]: toast.success,
          [NotificationType.Warning]: toast.warning,
          [NotificationType.Error]: toast.error,
        };
        notificationFunctions[notification.type](notification.message);
      });

      return () => {
        socketIOClient.disconnect();
      };
    }
  }, [user?.id, accessToken]);

  const value = useMemo(() => socket, [socket]);

  return (
    <WebSocketContext.Provider value={value}>
      {children}
      <ToastContainer />
    </WebSocketContext.Provider>
  );
}

export default WebSocketProvider;
