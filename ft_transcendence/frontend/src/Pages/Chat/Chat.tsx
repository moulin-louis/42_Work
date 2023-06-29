import _ from "lodash";
import React, {
  useContext,
  useState,
  useEffect,
  useRef,
  useCallback,
} from "react";
import { Channel, ChannelContext } from "../../Context/ChannelContext";
import { WebSocketContext } from "../../Context/WebSocketContext";
import "./Chat.css";
import SendButtonImg from "./../../Images/send-chat.svg";
import ChannelMembers from "./ChannelMembers";
import ChannelManagement from "./ChannelManagement";
import GameProposal from "./GameProposal";
import ChannelPassword from "./ChannelPassword";
import ChatIcon from "./../../Navigation/Sidebar/icons/Chat.svg";
import PlusIcon from "./../../Images/Plus.svg";
import MoreIcon from "./../../Images/More.svg";
import LeaveIcon from "./../../Images/Leave.svg";
import SettingsIcon from "./../../Images/Settings.svg";
import UserIcon from "./../../Images/User.svg";
import Dropdown from "react-bootstrap/Dropdown";
import InviteIcon from "./../../Images/PlayIc.svg";
import { ModalType } from "./ChatContainer";
import { useAuth } from "../../Context/AuthContext";
import { UsersContext } from "../../Context/UsersContext";
import UserProfile from "./UserProfile";
import { useNavigate} from "react-router-dom";
import PopupNewGame from "../Game/GamePopup"
import {useGameState} from "../Game/Game"
/**
 * Interface representing a single message
 */
export interface Message {
  date: Date;
  message: string;
  from: string;
  avatarUrl: string;
}

/**
 * Main Chat component for handling chat operations in the application.
 * @param {any} prop.messages - A collection of messages in the current chat.
 * @param {any} prop.toUserId - The id of the user the current user is chatting with.
 * @param {any} prop.toChannelId - The id of the channel the current user is in.
 * @param {any} prop.modal - The current modal type state.
 * @param {any} prop.setModal - The function to set the modal type.
 * @param {any} prop.selectedUser - The function to сheck - selected user or not.
 * @returns JSX.Element - A JSX element representing the chat interface.
 */
function Chat({
  messages,
  toUserId,
  toChannelId,
  setDestination,
  modal,
  setModal,
  selectedUser,
}: {
  messages: Message[];
  toUserId?: string;
  toChannelId: string;
  setDestination?: any;
  modal: ModalType;
  setModal: (model: ModalType) => void;
  selectedUser?: string;
}) {
  const { user } = useAuth();
  const channels = useContext(ChannelContext);
  const toChannel: Channel | undefined = toChannelId
    ? channels[toChannelId]
    : undefined;
  const users = useContext(UsersContext);

  const [toUser, setToUser] = useState(users.find((u) => u.id === toUserId));
  const { LaunchGame, waitingGame, startMatchmaking, setWaitingGame, handleGameOver } = useGameState();

  const mm_chat = (mode:any) => {
    socket?.emit('create_game_proposal', {
      recipient: toUserId,
      game_mode: mode.game_mode,
      limit_max: mode.limit_max,
    });
  }
  useEffect(() => {
    setToUser(users.find((u) => u.id === toUserId));
  }, [toUserId, users]);

  const socket = useContext(WebSocketContext);
  const isAdminChannel = () => toChannel?.admins?.includes(user?.id ?? "");
  const isOwnerChannel = () => toChannel?.owner === (user?.id ?? "");
  const isBannedChannel = () => toChannel?.bans?.includes(user?.id ?? "");
  const isMutedChannel = () => toChannel?.mutes?.includes(user?.id ?? "");
  const messagesEndRef = useRef<HTMLDivElement | null>(null);
  const scrollToBottom = () => {
    messagesEndRef.current?.scrollIntoView({ behavior: "smooth" });
  };
  // eslint-disable-next-line react-hooks/exhaustive-deps
  const debouncedSetRead = useCallback(
    _.debounce((user, toUserId, toChannelId) => {
      if (toUserId || toChannelId)
        socket?.emit("setread", {
          from: user?.id,
          toUserId,
          toChannelId,
        });
    }, 1000),
    [socket]
  );
  const setRead = () => {
    debouncedSetRead(user, toUserId, toChannelId);
  };
  const leave = () => {
    socket?.emit("leavechannel", {
      userId: user?.id ?? "",
      channelId: toChannelId,
    });
    setDestination({ toUserId: undefined, toChannelId: undefined });
  };
  const members = toChannel?.members ?? [];
  const bans = toChannel?.bans ?? [];
  const membersNotBanned = members.filter((m) => !bans.includes(m));
  useEffect(() => {
    setModal(ModalType.NOTVISIBLE);
  }, [setModal, toChannelId]);
  useEffect(scrollToBottom, [messages]);
  useEffect(setRead, [
    socket,
    messages,
    user,
    toUserId,
    toChannelId,
    debouncedSetRead,
  ]);
  if (!selectedUser && !toChannelId) {
    return (
      <div className="chat-container choose-user-area">
        <div className="choose-user-heading">
          <img
            alt=""
            src={ChatIcon}
            width="40"
            height="40"
            className="d-inline-block align-top sidebar-icon choose-user-icon"
          />
          <h2 className="">
            Select a chat room<br></br>or create a new one
          </h2>
        </div>
      </div>
    );
  }
  return (
    <>
      <div className="chat-container">
        <div className="chat-header">
          <div className="margin-auto-panel">
            <div className="box-with-icon">
              <div className="margin-auto-panel box-with-icon" onClick={() => setModal(ModalType.USERPROFILE)}>
                <div className="user-avatar-container">
                  {toUser?.username.charAt(0) ??
                    toChannel?.name.charAt(0) ??
                    ""}
                </div>
                <div className="margin-auto-panel margin-panel-chat-settings chat-hide-mob">
                  {toUser?.username ?? toChannel?.name}
                </div>
              </div>
              <div className="box-with-icon margin-auto-panel">
                {isBannedChannel() && (
                  <div className="mini-badge-ban">You are banned</div>
                )}
                {isOwnerChannel() && (
                  <div className="mini-badge-users">
                    {membersNotBanned.length} members
                  </div>
                )}
                {isOwnerChannel() && (
                  <div className="mini-bage-admin">You are the owner</div>
                )}
                {!isOwnerChannel() && isAdminChannel() && (
                  <div className="mini-bage-admin admin-color-mini">
                    You are the admin
                  </div>
                )}
              </div>
            </div>
          </div>
          <div className="chat-popup-button-margin box-with-icon">
            {toChannelId && (
              <button
                onClick={() => setModal(ModalType.ADDMEMBERS)}
                title="Add member"
                className="line-zero-chat"
              >
                <img
                  alt=""
                  src={PlusIcon}
                  width="20"
                  height="20"
                  className="d-inline-block align-top sidebar-icon"
                />
              </button>
            )}
            {toChannel && <Dropdown className="menu-toogle margin-panel-chat-settings">
              <Dropdown.Toggle variant="" id="dropdown-basic">
                <img
                  alt=""
                  src={MoreIcon}
                  width="20"
                  height="20"
                  className="d-inline-block align-top sidebar-icon"
                />
              </Dropdown.Toggle>

              <Dropdown.Menu className="chat-dropdown-style">
                {isAdminChannel() && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => setModal(ModalType.MANAGEMEMBERS)}
                  >
                    <div className="box-with-icon">
                      <div>
                        <img
                          alt=""
                          src={UserIcon}
                          width="20"
                          height="20"
                          className="sidebar-icon dropdown-icon-button"
                        />
                      </div>
                      <div className="dropdown-name-button">Manage members</div>
                    </div>
                  </Dropdown.Item>
                )}
                {isOwnerChannel() && (
                  <Dropdown.Item
                    className="chat-drop-menu-item"
                    onClick={() => setModal(ModalType.CHANGEPASSWORD)}
                  >
                    <div className="box-with-icon">
                      <div>
                        <img
                          alt=""
                          src={SettingsIcon}
                          width="20"
                          height="20"
                          className="sidebar-icon dropdown-icon-button"
                        />
                      </div>
                      <div className="dropdown-name-button">
                        Change password
                      </div>
                    </div>
                  </Dropdown.Item>
                )}
                {(isAdminChannel() || isOwnerChannel()) && <div className="border-top-chat"></div>}
                {toChannelId && (
                  <Dropdown.Item
                    onClick={leave}
                    className="chat-drop-menu-item"
                  >
                    <div className="box-with-icon">
                      <div>
                        <img
                          alt=""
                          src={LeaveIcon}
                          width="20"
                          height="20"
                          className="sidebar-icon dropdown-icon-button"
                        />
                      </div>
                      <div className="dropdown-name-button">Leave</div>
                    </div>
                  </Dropdown.Item>
                )}
              </Dropdown.Menu>
            </Dropdown>}
            {modal === ModalType.ADDMEMBERS && (
              <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
                <ChannelMembers
                  onClose={() => setModal(ModalType.NOTVISIBLE)}
                  channel={toChannel}
                />
              </ModalOverlay>
            )}
            {modal === ModalType.MANAGEMEMBERS && (
              <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
                <ChannelManagement
                  onClose={() => setModal(ModalType.NOTVISIBLE)}
                  channel={toChannel}
                  owner={isOwnerChannel()}
                />
              </ModalOverlay>
            )}
            {modal === ModalType.CHANGEPASSWORD && (
              <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
                <ChannelPassword
                  onClose={() => setModal(ModalType.NOTVISIBLE)}
                />
              </ModalOverlay>
            )}
            {modal === ModalType.USERPROFILE && toUser && (
              <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
                <UserProfile
                  onClose={() => setModal(ModalType.NOTVISIBLE)} friend={toUser}
                />
              </ModalOverlay>
            )}
            {modal === ModalType.GAMEPROPOSAL && toUser && (
              <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
                <GameProposal
                  onClose={() => setModal(ModalType.NOTVISIBLE)}
                />
              </ModalOverlay>
            )}
          </div>
        </div>
        <div className="chat-history">
          {messages.length > 0 ? (
            _(messages)
              .sortBy("date")
              .map((message) =>
                message.from === user?.id ? (
                  <div
                    key={String(message.date)}
                    className={`message-sent fadeIn ${message === messages[messages.length - 1]
                      ? "message-enter-active"
                      : "message-enter"
                      }`}
                  >
                    <div className="chat-box-area">
                      <div className="message-box">{message.message}</div>
                      <div
                        className={`message-avatar-sent${message.avatarUrl ? "" : " no-avatar-sent"
                          }`}
                      >
                        {message.avatarUrl && (
                          <img src={message.avatarUrl} alt="Avatar" />
                        )}
                      </div>
                    </div>
                    <div className="message-time">
                      {new Date(message.date).toLocaleTimeString()}
                    </div>
                  </div>
                ) : (
                  <div
                    key={String(message.date)}
                    className={`message-received fadeIn ${message === messages[messages.length - 1]
                      ? "message-enter-active"
                      : "message-enter"
                      }`}
                  >
                    <div className="chat-box-area-r">
                      <div
                        className={`message-avatar-received${message.avatarUrl ? "" : " no-avatar"
                          }`}
                      >
                        {message.avatarUrl && (
                          <img src={message.avatarUrl} alt="Avatar" />
                        )}
                      </div>
                      <div className="message-box-recieve">
                        {message.message}
                      </div>
                    </div>
                    <div className="message-time-r">
                      {new Date(message.date).toLocaleTimeString()}
                    </div>
                  </div>
                )
              )
              .value()
          ) : (
            <div className="empty-chat-message">
              No messages yet.{" "}
              <b>
                <span className="empty-chat-message-green">Say Hello!</span>
              </b>
              <div>
                <button
                  className="auth-button empty-chat-message"
                  onClick={() => {
                    if (socket) {
                      const message = toChannelId
                        ? "Hi, all!"
                        : `Hello, ${toUser?.username}!`;
                      socket.emit("newmessage", {
                        message,
                        from: user?.id ?? "",
                        toUserId,
                        toChannelId,
                      });
                    }
                  }}
                >
                  Say Hello
                </button>
              </div>
            </div>
          )}
          <div ref={messagesEndRef} />
        </div>

        <Input
          from={user?.id ?? ""}
          toUserId={toUserId ?? ""}
          toChannelId={toChannelId ?? ""}
          isBan={isBannedChannel() ?? false}
          isMuted={isMutedChannel() ?? false}
          startMatchmaking={mm_chat}
        />
      </div>
    </>
  );
}

/**
 * Sub-component for handling input in the chat
 * @param {string} prop.from - Id of the user sending the message
 * @param {string} prop.toUserId - Id of the user to whom the message is addressed
 * @param {string} prop.toChannelId - Id of the channel to which the message is addressed
 * @param {boolean} prop.isBan - Whether the user is banned from the channel
 */
function Input({
    from,
    toUserId,
    toChannelId,
    isBan,
    isMuted,
    startMatchmaking
  }: {
  from: string;
  toUserId: string | undefined;
  toChannelId: string | undefined;
  isBan: boolean;
  isMuted: boolean;
  startMatchmaking: (mode:any ) => void;
}) {
  const [message, setMessage] = useState<string>("");
  const socket = useContext(WebSocketContext);
  const navigate = useNavigate();
  const inputRef = useRef<HTMLInputElement>(null);

  useEffect(() => {
    inputRef.current?.focus();
  }, [toUserId, toChannelId]);

  const handleMessageChange = (event: React.ChangeEvent<HTMLInputElement>) =>
    setMessage(event.target.value);

  const handleKeyPress = (event: React.KeyboardEvent) => {
    if (event.key === "Enter" && !event.shiftKey) {
      event.preventDefault();
      sendMessage();
    }
  };

  const sendMessage = () => {
    if (!message.trim()) {
      return;
    }

    socket?.emit("newmessage", { message, from, toUserId, toChannelId });
    socket?.emit("setread", { from, toUserId, toChannelId });
    setMessage("");
  };

  const [showChannelMembers, setShowChannelMembers] = useState(false);

  const handleAddFriendClick = () => {
    setShowChannelMembers(true);
  };

  const handleClose = () => {
    setShowChannelMembers(false);
  };

  return (
    <>
      <div className="chat-input col-xl-8 col-lg-12">
        <div className="col-xl-11 chat-input-mob">
          <div className="input-chat-with-button">
            {toUserId && <img
              alt=""
              src={InviteIcon}
              width="15"
              height="15"
              onClick={handleAddFriendClick}
              className=""
              style={{ cursor: "pointer" }}
            />}
            {showChannelMembers && (
              <ModalOverlay onClose={handleClose}>
                <PopupNewGame onClose={handleClose} startMatchmaking={startMatchmaking} />
              </ModalOverlay>
            )}
            <input
              type="text"
              value={message}
              onChange={handleMessageChange}
              onKeyDown={handleKeyPress}
              placeholder="Type a message here..."
              className="input-message"
              ref={inputRef}
              disabled={(!toUserId && !toChannelId) || isBan || isMuted}
            />
          </div>
        </div>
        <div className="col-xl-1">
          <img
            alt=""
            src={SendButtonImg}
            width="40"
            height="40"
            onClick={sendMessage}
            className="chat-button"
          />
        </div>
      </div>
    </>
  );
}

interface ModalOverlayProps {
  onClose: () => void;
  children?: React.ReactNode;
}

export function ModalOverlay({ onClose, children }: ModalOverlayProps) {
  return (
    <div className="chat-popup-overlay">
      <div>{children}</div>
    </div>
  );
}

export default Chat;
