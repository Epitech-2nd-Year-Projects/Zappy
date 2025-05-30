PYTHON    := python3
LINTER    := flake8
TESTS     := tests/
VENV_DIR  := .venv

.PHONY: all clean test lint

all: lint test

lint:
	$(LINTER) src/

test:
	$(PYTHON) -m pytest $(TESTS)

clean:
	$(RM) -r $(VENV_DIR) __pycache__ .pytest_cache