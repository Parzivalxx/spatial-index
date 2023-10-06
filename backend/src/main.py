from fastapi import FastAPI


app = FastAPI()

from routes.routes import generate_points  # noqa
