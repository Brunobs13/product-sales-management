# Product Sales Management (MVC Architecture)

A production-style C project that transforms a monolithic sales script into a modular MVC codebase with tests, CI, and professional documentation.

## Project Overview

This repository implements a **Product Sales Management** system using a clean **MVC architecture** in C. It supports product lifecycle operations (create/update/delete), sales ingestion, and report generation with clear separation between controllers, repositories, services, and views.

## Business Problem

Small retail operations often track products and sales in ad-hoc spreadsheets, making reporting inconsistent and error-prone. The project addresses this by providing a deterministic command-line system that:

- manages product inventory metadata
- records and validates sales transactions
- produces reproducible sales KPIs
- preserves state through CSV persistence

## Architecture Diagram (Textual)

```
[View Layer: console_view]
        |
        v
[Controller Layer: product_controller, report_controller]
        |
        v
[Service Layer: report_service]
        |
        v
[Repository Layer: product_repository, sale_repository]
        |
        v
[Data Sources: data/products.csv, data/sales.csv]
```

### MVC Mapping

- **Model**: `Product`, `Sale`, `ProductCatalog`, `SalesRegistry`
- **View**: terminal rendering and user input helpers
- **Controller**: menu actions, orchestration, and user flow
- **Service**: report calculations and business metrics
- **Repository**: CSV I/O, data validation, and persistence

## Tech Stack

- C11
- GCC / Clang compatible build
- Makefile-based build system
- GitHub Actions for CI
- CSV data persistence

## Project Structure

```
.
├── .github/workflows/ci.yml
├── configs/
│   └── app.env.example
├── data/
│   ├── products.csv
│   └── sales.csv
├── docs/
│   ├── portfolio_ready.md
│   ├── repository_audit.md
│   └── technical_deep_dive.md
├── include/
│   ├── controllers/
│   ├── core/
│   ├── models/
│   ├── repositories/
│   ├── services/
│   └── views/
├── legacy/
│   └── ProgramasDeVendas.c
├── src/
│   ├── controllers/
│   ├── repositories/
│   ├── services/
│   ├── views/
│   └── main.c
├── tests/
│   ├── test_product_repository.c
│   └── test_report_service.c
├── .env.example
├── .gitignore
└── Makefile
```

## Setup Instructions

1. Clone the repository:

```bash
git clone https://github.com/Brunobs13/product-sales-management.git
cd product-sales-management
```

2. Build the project:

```bash
make all
```

3. (Optional) configure runtime paths:

```bash
cp .env.example .env
export $(cat .env | xargs)
```

4. Run the application:

```bash
make run
```

5. Run tests:

```bash
make test
```

## CI/CD Overview

The CI pipeline (`.github/workflows/ci.yml`) runs on push and pull requests.

- compiles the project (`make all`)
- executes unit tests (`make test`)
- blocks regressions before merge

## Data Versioning Strategy

Current state uses versioned CSV snapshots in Git for deterministic local execution. For larger datasets and collaborative workflows, the next step is integrating DVC with a remote backend (S3/DagsHub) and storing immutable dataset versions per release tag.

## Model Tracking Strategy

This project is currently rule-based (non-ML). If forecasting or demand prediction is introduced, MLflow should track:

- experiment parameters
- model metrics
- model artifacts
- model promotion lifecycle

## Deployment Strategy

Current deployment target is local CLI execution. Production hardening path:

1. package binary via release pipeline
2. create containerized runtime image
3. deploy with environment-specific configs
4. expose reporting through API layer (future extension)

## Security Considerations

- no credentials are hardcoded
- runtime data paths are controlled by environment variables
- `.gitignore` blocks local secrets and artifacts
- legacy monolith kept isolated under `legacy/` for auditability
- input validation enforces numeric/date constraints

## Lessons Learned

- splitting a monolith into MVC reduces change risk and clarifies responsibilities
- repositories + services make business logic testable without UI coupling
- build automation and CI are mandatory even for C CLI projects

## Future Improvements

1. Add transactional file locking for concurrent writes.
2. Add structured logging and operational audit trail.
3. Add API adapter layer (REST/gRPC) for external integrations.
4. Introduce DVC for data lineage and remote dataset governance.
5. Add observability metrics (Prometheus/OpenTelemetry bridge).

## Additional Technical Documents

- Audit report: `docs/repository_audit.md`
- Deep technical analysis: `docs/technical_deep_dive.md`
- Portfolio-ready narratives: `docs/portfolio_ready.md`
