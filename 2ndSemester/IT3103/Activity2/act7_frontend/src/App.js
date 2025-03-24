import React, { useEffect, useState } from "react";
import { ApolloClient, InMemoryCache, ApolloProvider, useQuery, useMutation, useSubscription, gql, split, HttpLink } from "@apollo/client";
import { WebSocketLink } from "@apollo/client/link/ws";
import { getMainDefinition } from "@apollo/client/utilities";
import "./index.css";

// GraphQL Queries & Mutations
const GET_POSTS = gql`
  query GetPosts {
    posts {
      id
      title
      content
    }
  }
`;

const CREATE_POST = gql`
  mutation CreatePost($title: String!, $content: String!, $userId: ID!) {
    createPost(title: $title, content: $content, userId: $userId) {
      id
      title
      content
      userId
    }
  }
`;

const POST_ADDED = gql`
  subscription OnPostAdded {
    postAdded {
      id
      title
      content
    }
  }
`;

// Create an HTTP link for queries and mutations
const httpLink = new HttpLink({
  uri: "http://localhost:4002/graphql",
});

// Create a WebSocket link for subscriptions
const wsLink = new WebSocketLink({
  uri: "ws://localhost:4002/graphql",
  options: {
    reconnect: true,
  },
});

// Split links based on operation type
const splitLink = split(
  ({ query }) => {
    const definition = getMainDefinition(query);
    return (
      definition.kind === "OperationDefinition" &&
      definition.operation === "subscription"
    );
  },
  wsLink,
  httpLink
);

const client = new ApolloClient({
  link: splitLink,
  cache: new InMemoryCache(),
});

const PostsTable = () => {
  const { loading, error, data } = useQuery(GET_POSTS);
  const { data: subscriptionData } = useSubscription(POST_ADDED);
  const [createPost] = useMutation(CREATE_POST);
  const [posts, setPosts] = useState([]);
  const [title, setTitle] = useState("");
  const [content, setContent] = useState("");

  useEffect(() => {
    if (data) setPosts(data.posts);
  }, [data]);

  useEffect(() => {
    if (subscriptionData) {
      setPosts((prevPosts) => [subscriptionData.postAdded, ...prevPosts]);
    }
  }, [subscriptionData]);

  const handleCreatePost = async () => {
    if (!title.trim() || !content.trim()) return;
    await createPost({ variables: { title, content } });
    setTitle("");
    setContent("");
  };

  if (loading) return <p className="loading">Loading...</p>;
  if (error) return <p className="error">Error loading posts.</p>;

  return (
    <div className="container">
      <h1>Posts</h1>
      <div className="form">
        <input
          value={title}
          onChange={(e) => setTitle(e.target.value)}
          placeholder="Title"
        />
        <input
          value={content}
          onChange={(e) => setContent(e.target.value)}
          placeholder="Content"
        />
        <button onClick={handleCreatePost}>Create Post</button>
      </div>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Title</th>
            <th>Content</th>
            <th>UserID</th>
          </tr>
        </thead>
        <tbody>
          {posts.length > 0 ? (
            posts.map((post) => (
              post ? (
                <tr key={post.id}>
                  <td>{post.id}</td>
                  <td>{post.title}</td>
                  <td>{post.content}</td>
                  <td>{post.userId}</td>
                </tr>
              ) : null
            ))
          ) : (
            <tr>
              <td colSpan="3">No posts available</td>
            </tr>
          )}
        </tbody>
      </table>
    </div>
  );
};

const App = () => (
  <ApolloProvider client={client}>
    <div className="app">
      <PostsTable />
    </div>
  </ApolloProvider>
);

export default App;