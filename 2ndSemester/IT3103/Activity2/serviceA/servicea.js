import amqp from "amqplib";
import fetch from "node-fetch";

const QUEUE_NAME = "posts";

// GraphQL mutation to insert a post
const CREATE_POST_MUTATION = `
  mutation CreatePost($title: String!, $content: String!) {
    createPost(title: $title, content: $content) {
      id
      title
      content
    }
  }
`;

const insertPost = async (post) => {
  try {
    const response = await fetch("http://localhost:4002/graphql", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        query: CREATE_POST_MUTATION,
        variables: { title: post.title, content: post.content },
      }),
    });

    const result = await response.json();
    console.log("GraphQL Response:", result);

    if (result.errors) {
      console.error("GraphQL Errors:", result.errors);
      return;
    }

    console.log("Post inserted:", result.data.createPost);
  } catch (error) {
    console.error("Error inserting post:", error);
  }
};

const subscribeToPosts = async () => {
  try {
    const connection = await amqp.connect("amqp://localhost");
    const channel = await connection.createChannel();

    await channel.assertQueue(QUEUE_NAME, { durable: true });

    console.log("Waiting for messages in queue:", QUEUE_NAME);

    channel.consume(
      QUEUE_NAME,
      async (message) => {
        const post = JSON.parse(message.content.toString());
        console.log("Received post:", post);

        await insertPost(post);

        channel.ack(message);
      },
      { noAck: false }
    );
  } catch (error) {
    console.error("Error subscribing to posts:", error);
  }
};

subscribeToPosts();