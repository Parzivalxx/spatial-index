#!/bin/sh

rm -rf .venv build dist spatial_index*

poetry shell
poetry install

python setup.py install
