# 002 - Replace Repository Layer with Domain Interfaces

## Context
Repository layer was tightly coupled to persistence logic.

## Decision
Split into:
- Domain interfaces
- Infrastructure implementations

## Benefits
+ Easier extensibility
+ Better separation of concerns
+ Cleaner Clean Architecture boundaries