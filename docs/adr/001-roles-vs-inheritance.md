# 001 - Composition over Inheritance for User Roles

## Context
Originally, roles like Student and Worker inherited from Person.

## Problem
Inheritance caused:
- Class explosion (StudentEmployeePhDTeacher)
- No runtime role extension without recreating objects

## Decision
Use composition:
Person contains vector<Role> instead of subclassing.

## Consequences
+ Easier to add roles dynamically
+ No class explosion
+ More flexible domain model
- Slightly more logic in role handling