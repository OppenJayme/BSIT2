## 🏗️ Building Microservices with Database Migrations & GraphQL CRUD Endpoints

This project consists of two microservices: Users and Posts, each with its own database, GraphQL API, and CRUD operations. It demonstrates how to use Prisma for database migrations and Apollo Server for handling GraphQL requests.

## 📌 Project Overview

Tech Stack

- Node.js (Runtime environment)
- Prisma (ORM for database migrations & queries)
- Apollo Server (GraphQL server)
- SQLite (Lightweight database)
- Each microservice is self-contained, runs on a separate port, and has its own database.

## Instructions

For this activity, you will create two microservices—"Users" and "Posts"—each with its own database. You’ll apply database migrations and set up GraphQL endpoints for CRUD operations. Complete the following requirements:

1. Set up two separate microservices folders: users-service and posts-service.
2. Initialize a Node.js project in each folder with necessary dependencies (e.g., Prisma, Apollo Server, SQLite).
3. For each microservice:
   - Configure a Prisma schema with a model (User for users-service, Post for posts-service) including at least an id and two other fields.
   - Apply a database migration to create the database and table.
4. Implement a GraphQL server in each microservice using Apollo Server:
   - Define a schema with types for the model and queries/mutations for CRUD operations (create, read, update, delete).
   - Write resolvers to handle all CRUD operations using Prisma.
   - Run each service on a different port (e.g., 4001 for Users, 4002 for Posts).
5. Test all CRUD endpoints for both services using a GraphQL client (e.g., GraphiQL):
   - Verify you can create, read, update, and delete records in each database.

## Reflection Questions

What do database migrations do and why are they useful?
How does GraphQL differ from REST for CRUD operations?

## stupid errors

- becareful of version compatibility here bcs the versions have to be downgraded

## versions used/changed in this project

- graphql-subscriptions@2.0.0.
  - The asyncIterator function was removed in the earliest version @3.0.0.
  - @2.0.0 keeps the asyncIterator function working.
- graphql-ws@5.9.1
  - The reason for this is because the useServer function is not being used/removed at the earliest versions of the websocket.

## new Update Act 10
- Message queue system used RabbitMQ
- Fixed websocket subprotocol Mismatch
   - ws is using graphql-ws which uses the graphql-transport-ws but the frontend is using subscriptions-transport-ws.
- Real-time update fixed
- Fixed the UseEffect for subscriptions data in frontend
- Fixed the handlecreatePost function in the frontend
- added debugging logs
