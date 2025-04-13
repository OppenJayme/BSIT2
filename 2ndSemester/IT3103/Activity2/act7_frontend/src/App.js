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
  const [currentPage, setCurrentPage] = useState(1); // Current page
  const postsPerPage = 10; // Number of posts per page

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

  // Calculate the posts to display on the current page
  const indexOfLastPost = currentPage * postsPerPage;
  const indexOfFirstPost = indexOfLastPost - postsPerPage;
  const currentPosts = posts.slice(indexOfFirstPost, indexOfLastPost);

  // Handle page navigation
  const nextPage = () => {
    if (currentPage < Math.ceil(posts.length / postsPerPage)) {
      setCurrentPage(currentPage + 1);
    }
  };

  const prevPage = () => {
    if (currentPage > 1) {
      setCurrentPage(currentPage - 1);
    }
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
          </tr>
        </thead>
        <tbody>
          {currentPosts.length > 0 ? (
            currentPosts.map((post) => (
              post ? (
                <tr key={post.id}>
                  <td>{post.id}</td>
                  <td>{post.title}</td>
                  <td>{post.content}</td>
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
      <div className="pagination">
        <button onClick={prevPage} disabled={currentPage === 1}>
          Previous
        </button>
        <span>
          Page {currentPage} of {Math.ceil(posts.length / postsPerPage)}
        </span>
        <button
          onClick={nextPage}
          disabled={currentPage === Math.ceil(posts.length / postsPerPage)}
        >
          Next
        </button>
      </div>
    </div>
  );
};

const App = () => (
  <ApolloProvider client={client}>
    <div className="app">
      <img
        className="character"
        src="https://www.pngall.com/wp-content/uploads/15/Xiao-PNG-Images.png"
        alt="Character"
      />
      <img
        className="primo"
        src="https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/i/600cc6ca-4f52-40e6-a83c-3bcd6e94e0ee/depbq7u-8d5c23aa-8eeb-435f-89c5-a87238cb052d.png"
        alt="Primogems"/>
      <PostsTable />
    </div>
  </ApolloProvider>
);

export default App;

