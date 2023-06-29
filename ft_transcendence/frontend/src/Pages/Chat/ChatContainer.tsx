import React, { useContext, useEffect, useState } from "react";
import {useNavigate} from "react-router-dom";
import _ from "lodash";
import "./Chat.css";
import Header from "../../Navigation/Header/Header";
import Sidebar from "../../Navigation/Sidebar/Sidebar";
import Container from "react-bootstrap/Container";
import Row from "react-bootstrap/Row";
import Col from "react-bootstrap/Col";
import { MessageStore, MessagesContext } from "../../Context/ChatContext";
import Chat, { Message, ModalOverlay } from "./Chat";
import { UnreadContext, UnreadStore } from "../../Context/UnreadContext";
import { ChannelContext, ChannelStore } from "../../Context/ChannelContext";
import ChannelCreation from "./ChannelCreation";
import ChannelJoin from "./ChannelJoin";
import AddChatImg from "./../../Images/add-chat.svg";
import SearchChatIcon from "./../../Images/search-channel.svg";
import { User, useAuth } from "../../Context/AuthContext";
import { UsersContext } from "../../Context/UsersContext";
import { WebSocketContext } from "../../Context/WebSocketContext";


/**
 * ModalType enum for handling different types of modals in the chat container.
 */
export enum ModalType {
  NOTVISIBLE,
  CHANNELCREATION,
  CHANNELJOIN,
  ADDMEMBERS,
  MANAGEMEMBERS,
  CHANGEPASSWORD,
  ADDMODAL,
  USERPROFILE,
  GAMEPROPOSAL,
}

/**
 * The main ChatContainer component that is responsible for displaying the chat interface.
 * It takes care of the state management for messages, selected chat, and the modal type.
 * It fetches the messages based on the destination from the context and renders
 * different parts of the chat interface like Header, Sidebar, Selection panel, and Chat.
 */

function ChatContainer() {
  const [messages, setMessages] = useState<Message[]>([]);
  const [destination, setDestination] = useState<{
    toUserId?: string;
    toChannelId?: string;
  }>();
  const [selectedId, setSelectedId] = useState<string>("");
  const messageStore: MessageStore = useContext(MessagesContext);
  const [modal, setModal] = useState<ModalType>(ModalType.NOTVISIBLE);
  const socket = useContext(WebSocketContext);
  const navigate = useNavigate();
  // For mobile version
  const [isChatSelected] = useState(false);

  useEffect(() => {
    socket?.on('update_modal', (payload: ModalType) => {
      setModal(payload);
    });
    return () => {
      socket?.off('update_modal');
    };
  }, [socket]);

  useEffect(() => {
    socket?.on('launch_game_proposal', (payload: any) => {
      socket.emit('matchmaking', {game_mode: payload.game_mode, limit_max: payload.limit_max});
      navigate('/play', {state: { mode: true }});
    });
    return (): void => {
      socket?.off('launch_game_proposal');
    };
  }, [socket, navigate]);

  useEffect(() => {
    const key = destination?.toUserId
      ? `users.${destination?.toUserId}`
      : `channels.${destination?.toChannelId}`;
    setMessages(_.get(messageStore, key, []));
  }, [messageStore, destination]);

  return (
    <>
      <Header />
      <Container>
        <Row className="zero-margin">
          <Col lg={12} xl={2} className="sidebar-global">
            <Sidebar />
          </Col>
          <Col lg={12} xl={2} className={`chat-sidebar ${selectedId ? 'chat-mobile-hidden' : 'chat-mobile'}`}>
            <Selection
              setDestination={setDestination}
              selectedId={selectedId}
              setSelectedId={setSelectedId}
              modal={modal}
              setModal={setModal}
            />
          </Col>
          <Col lg={12} xl={8} className="chat-area">
            <Chat
              messages={messages}
              toUserId={destination?.toUserId}
              toChannelId={destination?.toChannelId ?? ""}
              setDestination={setDestination}
              selectedUser={destination?.toUserId ?? ""}
              modal={modal}
              setModal={setModal}
            />
            {selectedId && (
              <button
              onClick={() => {
                setSelectedId("");
                setDestination({ toUserId: undefined, toChannelId: undefined });
              }}
                className="return-button">
                ← Back to all chats
              </button>
            )}
          </Col>
        </Row>
      </Container>
    </>
  );
}

/**
 * The Selection component is responsible for the user's selection of chat destination. It has two sections -
 * Channels and Users. It maintains the state of selected chat and also sets the destination
 * based on user selection.
 * @param {function} prop.setDestination - Function to set the chat destination.
 * @param {string} prop.selectedId - The ID of the currently selected chat.
 * @param {function} prop.setSelectedId - Function to set the selected chat ID.
 * @param {ModalType} prop.modal - The type of modal currently visible in the chat interface.
 * @param {function} prop.setModal - Function to set the modal type.
 */
function Selection({
  setDestination,
  selectedId,
  setSelectedId,
  modal,
  setModal,
}: {
  setDestination: any;
  selectedId: string;
  setSelectedId: any;
  modal: ModalType;
  setModal: any;
}) {
  return (
    <>
      <Row className="zero-margin">
        <Col lg={12} xl={12} className="panel-padding">
          <Channels
            setDestination={setDestination}
            selectedId={selectedId}
            setSelectedId={setSelectedId}
            modal={modal}
            setModal={setModal}
          />
          <Users
            setDestination={setDestination}
            selectedId={selectedId}
            setSelectedId={setSelectedId}
          />
        </Col>
      </Row>
    </>
  );
}

/**
 * Channels component is responsible for displaying the list of channel chats.
 * It allows the user to select a channel and also provides options to create a new channel or join an existing one.
 * @param {function} prop.setDestination - Function to set the chat destination.
 * @param {string} prop.selectedId - The ID of the currently selected chat.
 * @param {function} prop.setSelectedId - Function to set the selected chat ID.
 * @param {ModalType} prop.modal - The type of modal currently visible in the chat interface.
 * @param {function} prop.setModal - Function to set the modal type.
 */
function Channels({
  setDestination,
  selectedId,
  setSelectedId,
  modal,
  setModal,
}: any) {
  const allChannels = useContext(ChannelContext);
  const { user } = useAuth();

  const channelsVisible = _(allChannels)
    .filter((channel) => channel.members?.includes(user?.id ?? ""))
    .filter((channel) => !channel.bans?.includes(user?.id ?? ""))
    .keyBy("name")
    .value();

  return (
    <>
      <div className="sidebar-box box-with-icon chat-padding-heading">
        <div style={{ marginBottom: "30px", display: "contents" }}>
          <h2 className="text-color-gray sidebar-element heading-box">
            {" "}
            Channels{" "}
          </h2>
          <div className="all-icons-chat">
            <img
              src={SearchChatIcon}
              alt={`Search channels`}
              className={"icon-chat"}
              onClick={() => setModal(ModalType.CHANNELJOIN)}
            />
            <img
              src={AddChatImg}
              alt={`Add channel`}
              className={"icon-chat"}
              onClick={() => setModal(ModalType.CHANNELCREATION)}
            />
          </div>
        </div>
        {modal === ModalType.CHANNELCREATION && (
          <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
            <ChannelCreation onClose={() => setModal(ModalType.NOTVISIBLE)} />
          </ModalOverlay>
        )}
        {modal === ModalType.CHANNELJOIN && (
          <ModalOverlay onClose={() => setModal(ModalType.NOTVISIBLE)}>
            <ChannelJoin onClose={() => setModal(ModalType.NOTVISIBLE)} />
          </ModalOverlay>
        )}
      </div>
      <div>
        <ChannelDisplay
          setDestination={setDestination}
          channels={channelsVisible}
          selectedId={selectedId}
          setSelectedId={setSelectedId}
        />
      </div>
    </>
  );
}

/**
 * ChannelDisplay component is responsible for displaying the information about all available channels.
 * This information includes the channel name, last message, unread messages count, and an icon
 * representing the privacy status of the channel (public/private).
 * @param {Array} prop.channels - Array containing information about all the available channels.
 * @param {string} prop.selectedId - The ID of the currently selected chat.
 * @param {function} prop.setSelectedId - Function to set the selected chat ID.
 * @param {function} prop.setDestination - Function to set the chat destination.
 */
function ChannelDisplay({
  channels,
  setDestination,
  selectedId,
  setSelectedId,
}: {
  channels: ChannelStore;
  setDestination: any;
  selectedId: string;
  setSelectedId: any;
}) {
  const messageStore: MessageStore = useContext(MessagesContext);
  const messsageCountByChannel =
    useContext<UnreadStore>(UnreadContext)?.countByChannels;
  const { user } = useAuth();
  const getLastMessage = (name: string): React.JSX.Element => {
    const messages = _.get(messageStore, `channels.${name}`, []);
    const lastMessage = messages[messages.length - 1];

    if (!lastMessage) {
      return <span style={{ color: "green" }}>Say Hello!</span>;
    }

    const messageSender =
      lastMessage.from === user?.username ? <strong>You: </strong> : "";
    return (
      <div className="last-message-text">
        {" "}
        {messageSender} {lastMessage.message}{" "}
      </div>
    );
  };

  const getUnreadMessagesCount = (channelId: string): number =>
    _(messsageCountByChannel).find({ channelId })?.unread ?? 0;

  return (
    <div>
      {_(channels)
        .map(({ id, name }: { id: string; name: string }) => (
          <div
            key={id}
            onClick={() => {
              setDestination({ toUserId: undefined, toChannelId: id });
              setSelectedId(id);
            }}
            style={id === selectedId ? { backgroundColor: "#fff" } : {}}
            className="user-display sidebar-box chat-padding-heading"
          >
            <div className="user-avatar-container">
              {name.charAt(0) ? name.charAt(0) : ""}
            </div>
            <div className="user-preview-box">
              <div className="user-name last-message-text">#{name}</div>
              <div className="last-message">{getLastMessage(id)}</div>
            </div>
            {getUnreadMessagesCount(id) > 0 && (
              <div className="unread-messages-count">
                {getUnreadMessagesCount(id) > 9
                  ? "9+"
                  : getUnreadMessagesCount(id)}
              </div>
            )}
          </div>
        ))
        .value()}
    </div>
  );
}

/**
 * The Users component, which uses the UsersContext to display users and handle user interaction.
 * @param {Function} props.setDestination - The function to set the destination user for messages.
 * @param {string} props.selectedId - The currently selected user id.
 * @param {Function} props.setSelectedId - The function to set the selected user id.
 * @returns {React.JSX.Element} The component that displays a list of users from the UsersContext.
 */
function Users({ setDestination, selectedId, setSelectedId }: any) {
  const users = useContext(UsersContext);
  return (
    <div>
      <div className="sidebar-box chat-padding-heading">
        <h2 className="text-color-gray sidebar-element heading-box">Friends</h2>
      </div>
      <UsersDisplay
        setDestination={setDestination}
        users={users}
        selectedId={selectedId}
        setSelectedId={setSelectedId}
      />
    </div>
  );
}

/**
 * UsersDisplay component displays all users along with their message information and online status.
 * @param {User[]} props.users - The list of users to be displayed.
 * @param {Function} props.setDestination - The function to set the destination user for messages.
 * @param {string} props.selectedId - The currently selected user id.
 * @param {Function} props.setSelectedId - The function to set the selected user id.
 * @returns {React.JSX.Element} The component displaying all users with their corresponding data.
 */
function UsersDisplay({
  users,
  setDestination,
  selectedId,
  setSelectedId,
}: {
  users: User[];
  setDestination: any;
  selectedId: string;
  setSelectedId: any;
}) {
  const { user } = useAuth();
  const messageStore: MessageStore = useContext(MessagesContext);
  const messsageCountByUsers =
    useContext<UnreadStore>(UnreadContext)?.countByUsers;

  const getLastMessage = (userId: string): React.JSX.Element => {
    const messages = _.get(messageStore, `users.${userId}`, []);
    const lastMessage = messages[messages.length - 1];

    if (!lastMessage) {
      return <span style={{ color: "green" }}>Say Hello!</span>;
    }

    const messageSender =
      lastMessage.from === userId ? <strong>You: </strong> : "";

    return (
      <div className="last-message-text">
        {messageSender}
        {lastMessage.message}
      </div>
    );
  };

  const getUnreadMessagesCount = (userId: string): number =>
    _(messsageCountByUsers).find({ userId })?.unread ?? 0;

  const isOnline = true;

  const checkOnline = (isOnline: boolean): React.JSX.Element | undefined => {
    if (isOnline) {
      return (
        <>
          <div className="online-status-message" />
        </>
      );
    }
  };

  return (
    <div>
      {users.filter(u => u.id !== user?.id && !u.isBanned && !u.hasBanned).map(({ id, username, avatar }) => (
        <div
          key={id}
          onClick={() => {
            setDestination({ toUserId: id, toChannelId: undefined });
            setSelectedId(id);
          }}
          style={id === selectedId ? { backgroundColor: "#fff" } : {}}
          className="user-display sidebar-box chat-padding-heading"
        >
          <Col lg={12} xl={3} className="padding-zero image-container">
            <img
              src={avatar ?? ""}
              alt={`${username}'s avatar`}
              className={`user-avatar${!avatar ? " no-avatar" : ""}`}
            />
            {checkOnline(isOnline)}
          </Col>
          <div className="user-preview-box">
            <div className="user-name last-message-text">{username}</div>
            <div className="last-message">{getLastMessage(id)}</div>
          </div>
          {getUnreadMessagesCount(id) > 0 && (
            <div className="unread-messages-count">
              {getUnreadMessagesCount(id) > 9
                ? "9+"
                : getUnreadMessagesCount(id)}
            </div>
          )}
        </div>
      ))}
    </div>
  );
}

export default ChatContainer;
