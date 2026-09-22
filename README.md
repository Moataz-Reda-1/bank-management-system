# Bank Management System

A console-based Bank Management System built in C++ that handles client accounts and bank transactions, with a role-based user permission system.

## Features

- **Client Management (CRUD)** — Add, update, delete, and search client accounts
- **Transactions** — Deposit and withdrawal operations with balance validation
- **Multi-User System** — Login/authentication with granular, bitwise-flag permissions per user (view clients, add, delete, update, transactions, manage users)
- **Access Control** — Each menu option checks the logged-in user's permissions before granting access
- **Persistent Storage** — Client and user data is saved to and loaded from text files using custom file handling
- **Soft Delete** — Records are marked as deleted rather than removed, preserving data integrity

## Tech Stack

- **Language:** C++
- **Concepts used:** Structs, Enums, STL (`vector`, `string`), File I/O

## How It Works

1. The program starts with a **Login Screen** where a user enters their username and password.
2. Once authenticated, the user sees the **Main Menu**, with options filtered based on their permissions.
3. Users with the right permissions can:
   - View the full client list
   - Add new clients
   - Delete or update existing clients
   - Search for a client by account number
   - Perform deposit/withdrawal transactions and view total balances
   - Manage other users (add, update, delete, list) — admin-level permission only

## Project Structure

- `stClient` — represents a bank client (account number, PIN, name, phone, balance)
- `stUser` — represents a system user (username, password, permissions)
- Data is serialized to/from text files using a custom delimiter (`#//#`)

## What I Learned

This project was built while learning the fundamentals of C++. It helped me practice:
- Structuring a real-world application with structs and enums
- Implementing a permission/access-control system using bitwise flags
- Reading and writing structured data to files
- Organizing a multi-menu console application with clean, reusable functions

## Status

This is a learning project and a work in progress — improvements planned include better input validation and potentially migrating file storage to a database.
