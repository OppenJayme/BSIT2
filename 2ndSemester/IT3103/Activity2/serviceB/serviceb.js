const amqp = require("amqplib");

const QUEUE_NAME = "posts";

const generateSyntheticPost = () => {
    const id = Math.floor(Math.random() * 1000);
    const title = `Post Title ${id}`;
    const content = `This is the content of post ${id}`;
    return { title, content };
  };

const publishPost = async () => {
  try {
    const connection = await amqp.connect("amqp://localhost");
    const channel = await connection.createChannel();

    await channel.assertQueue(QUEUE_NAME, { durable: true });

    const post = generateSyntheticPost();
    channel.sendToQueue(QUEUE_NAME, Buffer.from(JSON.stringify(post)));
    console.log("Published post:", post);

    setTimeout(() => {
      connection.close();
    }, 500);
  } catch (error) {
    console.error("Error publishing post:", error);
  }
};

// Publish a new post every 5 seconds
setInterval(publishPost, 5000);