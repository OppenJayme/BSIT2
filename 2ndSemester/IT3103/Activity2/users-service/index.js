const { ApolloServer, gql } = require("apollo-server-express");
const { PrismaClient } = require("@prisma/client");
const express = require("express");

const prisma = new PrismaClient();

const typeDefs = gql`
  type User {
    id: ID!
    name: String!
    email: String!
  }

  type Query {
    users: [User]
    user(id: ID!): User
  }

  type Mutation {
    createUser(name: String!, email: String!): User
    updateUser(id: ID!, name: String, email: String): User
    deleteUser(id: ID!): User
  }
`;

const resolvers = {
  Query: {
    users: () => prisma.user.findMany(),
    user: (_, { id }) => { 
      const userIdToQuery = id || userId;
      prisma.user.findUnique({ where: { id: Number(userIdToQuery) } });
    },
  },
  Mutation: {
    createUser: (_, args) => prisma.user.create({ data: args }),
    updateUser: (_, { id, ...args }) =>
      prisma.user.update({ where: { id: Number(id) }, data: args }),
    deleteUser: (_, { id }) =>
      prisma.user.delete({ where: { id: Number(id) } }),
  },
};

const app = express();

const server = new ApolloServer({
  typeDefs,
  resolvers,
  context: ({ req }) => {
    const userId = req.params.id ? Number(req.params.id) : null;
    return { userId };
  },
});

server.start().then(() => {
  server.applyMiddleware({ app });

  // Route to display a user page if the user exists
  app.get("/:id", async (req, res) => {
    const userId = parseInt(req.params.id); // Get the user ID from the URL
    try {
      const user = await prisma.user.findUnique({ where: { id: userId } }); // Query the database
      if (!user) {
        return res.status(404).send("User not found");
      }
      // If user exists, show their details
      res.send(`User Page for User ID: ${userId} <br> Name: ${user.name} <br> Email: ${user.email}`);
    } catch (error) {
      res.status(500).send("Error fetching user");
    }
  });

  app.listen({ port: 8010 }, () => {
    console.log(`🚀 Users service running at http://localhost:8010${server.graphqlPath}`);
  });
});