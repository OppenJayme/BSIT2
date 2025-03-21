import { ApolloServer } from '@apollo/server';
import { createServer } from 'http';
import { expressMiddleware } from '@apollo/server/express4';
import { ApolloServerPluginDrainHttpServer } from '@apollo/server/plugin/drainHttpServer';
import { makeExecutableSchema } from '@graphql-tools/schema';
import bodyParser from 'body-parser';
import express from 'express';
import { WebSocketServer } from 'ws';
import { useServer } from 'graphql-ws/lib/use/ws';
import { PubSub } from 'graphql-subscriptions';
import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();
const pubsub = new PubSub();
const POST_ADDED = 'POST_ADDED';

const port = 4002;

// GraphQL Schema
const typeDefs = `
  type Post {
    id: ID!
    title: String!
    content: String!
  }

  type Query {
    posts: [Post]
    post(id: ID!): Post
  }

  type Mutation {
    createPost(title: String!, content: String!): Post
    updatePost(id: ID!, title: String, content: String): Post
    deletePost(id: ID!): Post
  }

  type Subscription {
    postAdded: Post
  }
`;

// graphql resolvers
const resolvers = {
  Query: {
    posts: () => prisma.post.findMany(),
    post: (_, { id }) => prisma.post.findUnique({ where: { id: Number(id) } }),
  },
  Mutation: {
    createPost: async (_, args) => {
      const post = await prisma.post.create({ data: args });
      pubsub.publish(POST_ADDED, { postAdded: post }); // 📢 Publish to subscription
      return post;
    },
    updatePost: (_, { id, ...args }) =>
      prisma.post.update({ where: { id: Number(id) }, data: args }),
    deletePost: (_, { id }) =>
      prisma.post.delete({ where: { id: Number(id) } }),
  },
  Subscription: {
    postAdded: {
      subscribe: () => pubsub.asyncIterator([POST_ADDED]),
    },
  },
};

const schema = makeExecutableSchema({ typeDefs, resolvers });

const app = express();
const httpServer = createServer(app);

//WebSocket Server Setup
const wsServer = new WebSocketServer({
  server: httpServer,
  path: '/graphql',
});
const wsServerCleanup = useServer({ schema }, wsServer);

// Apollo Server Setup
const apolloServer = new ApolloServer({
  schema,
  plugins: [
    // Proper shutdown for the HTTP server.
    ApolloServerPluginDrainHttpServer({ httpServer }),
    {
      // Proper shutdown for the WebSocket server.
      async serverWillStart() {
        return {
          async drainServer() {
            await wsServerCleanup.dispose();
          },
        };
      },
    },
  ],
});

// Start Apollo Server
await apolloServer.start();

// Express Middleware for HTTP Queries
app.use('/graphql', bodyParser.json(), expressMiddleware(apolloServer));

// Start HTTP & WebSocket Server
httpServer.listen(port, () => {
  console.log(`🚀 Query endpoint ready at http://localhost:${port}/graphql`);
  console.log(`🔄 Subscription endpoint ready at ws://localhost:${port}/graphql`);
});
