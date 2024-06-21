import json
import os
from typing import Annotated, List
from fastapi.responses import JSONResponse
import uvicorn
from datetime import timedelta, datetime
from fastapi import Depends, FastAPI, File, Form, HTTPException, Query, Request,status, UploadFile
from pydantic import BaseModel
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from passlib.context import CryptContext
from jose import jwt, JWTError
from passlib.hash import bcrypt

app = FastAPI()
oauth_test = OAuth2PasswordBearer(tokenUrl ="token")
upload_directory = "/run/media/xafold/Games and Software/Task/utsavp/Fastapi_tutorial/files"

## BASIC CRUD operations and Query Paramters----------------------------------------------------------------------------------------------------------
# class Item(BaseModel):
#     name: str
#     description: str | None = None
#     price : float
#     tax_percent : float | None = None

# @app.get("/items/{item_id}")
# async def get_item(item_id: int, q: str | None = None, short: bool = False):
#     item = { "item_id": item_id}
#     if q:
#         item.update({"q": q})
#     if not short:
#         item.update({"message":"Lorem ipsum lorem ipsum"})
#     return item

# @app.post("/user")
# async def get_user(item: Item):
#     item_dict = item.model_dump()
#     if item.tax_percent:
#         price_with_tax = item.price - (item.price*item.tax_percent/100)
#         item_dict.update({"price_with_tax":price_with_tax})
#     return item_dict

# @app.get("/items")
# async def get_item(q: str | None = Query(None, max_length=10)):
#     item = { "item": [{"item_id": "dog"},{"item_id": "cat"}]}
#     if q:
#         item.update({"q":q})
#     return item

# @app.put("/items/{item_id}/user/{user_id}")
# async def get_food(item_id: int, user_id: int, q: str | None = Query(..., max_length=10, min_length=3)) -> dict:
#     item = {"iem":item_id}
#     if user_id:
#         item.update({"q":q})
#     return item

####### BASIC Security  in fastapi-------------------------------------------------------------------------------------------------------------------
fake_db = {
    "johndoe": dict(
        username="johndoe",
        full_name="Will Pau",
        email="wpau0@vkontakte.ru",
        hashed_password="$2a$10$Xiqh/vxspQlXzZAUdzS3MuBRTHo0cxeRLPMLTyk.zgcN/4xAiySNK",
        disabled=False
    ),
    "berni": dict(
        username="berni",
        full_name="Berni Bischoff",
        email="bbischoff0@domainmarket.com",
        hashed_password="fakehashedsecret1",
        disable=True
    ),
    "eva": dict(
        username="eva",
        full_name="Eva Smith",
        email="evasmith@example.com",
        hashed_password="fakehashedsecret2",
        disabled=True
    ),
    "adam": dict(
        username="adam",
        full_name="Adam Jones",
        email="adamjones@example.com",
        hashed_password="fakehashedsecret3",
        disabled=True
    ),
    "lisa": dict(
        username="lisa",
        full_name="Lisa Williams",
        email="lisawilliams@example.com",
        hashed_password="fakehashedsecret4",
        disabled=True
    ),
}

# # Takes the plain paswword and adds fakehashed infront of the password
# def fake_hashed_password(password: str):
#     return f"fakehashed{password}"

# # User (BaseModel) from pydantic   
# class User(BaseModel):
#     username: str
#     full_name : str | None = None
#     email: str | None = None
#     disabled : bool | None = None

# class UserInDB(User):
#     hashed_password : str

# # Extract the user info from database using the username as key
# def get_user(db, username: str):
#     if username in db:
#         user_dict = db[username]
#         return UserInDB(**user_dict)

# # Takes token as argument and pass database and token to get_user function
# def fake_token_decode(token: str):
#     return get_user(fake_db, token)

# # Returns the current user from given token
# async def get_current_user(token: str = Depends(oauth_test)):
#     username = token.split()[1]
#     user = fake_token_decode(username)
#     if not user:
#         raise HTTPException(
#             status_code= status.HTTP_401_UNAUTHORIZED,
#             detail= "Invalid Credentials",
#             headers={"WWW-Authenticate":"Bearer"}
#         )
#     return user

# # Checks whether the user is active or not and reurn current_user
# async def get_current_active_user(current_user: UserInDB = Depends(get_current_user)):
#     if current_user.disabled:
#         raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Not active user")
#     return current_user

# # Endpoint to login using the OAuth2PasswordRequestForm
# @app.post("/token")
# async def login(form_data: OAuth2PasswordRequestForm = Depends()):
#     user_dict = fake_db.get(form_data.username)
#     if not user_dict:
#         raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Incorrect username" )
#     user = UserInDB(**user_dict)
#     hashed_password = fake_hashed_password(form_data.password)
#     if not hashed_password == user.hashed_password:
#         raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Incorrect password" )
#     return{"access_token":user.username, "token_type": "Bearer Token"}

# # Endpoint to get the current user data 
# @app.get("/user/me")
# async def get_me(current_user: UserInDB = Depends(get_current_active_user)):
#     return current_user

# # Endpoint to get the token of logged in user
# @app.get("/user/token")
# async def read_item(token: str = Depends(oauth_test)):
#     return {"token": token}

####### JWT Authentication in fastapi------------------------------------------------------------------------------------------------------------------------
SECRET_KEY = "helloworldfromtheearthtomars"
ALGORITHM = 'HS256'
ACCESS_TOKEN_EXPIRE_MINUTES = 30

# Token Model for access
class Token(BaseModel):
    access_token: str
    token_type: str

class TokenData(BaseModel):
    username: str | None=None
    
# User (BaseModel) from pydantic   
class User(BaseModel):
    username: str
    full_name : str | None = None
    email: str | None = None
    disabled : bool | None = None

class UserInDB(User):
    hashed_password : str

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

def verify_password(plain_password: str, hashed_password: str):
    return pwd_context.verify(plain_password, hashed_password)

def get_password_hash(password):
    return pwd_context.hash(password)

# Extract the user info from database using the username as key
def get_user(db, username: str):
    if username in db:
        user_dict = db[username]
        return UserInDB(**user_dict)
    
def authenticate_user(fake_db, username:str, password:str):
    user = get_user(fake_db, username)
    if not user:
        return HTTPException(
            status_code= status.HTTP_401_UNAUTHORIZED,
            detail= "Invalid Username",
        )
    if not verify_password(password, user.hashed_password):
        return HTTPException(
            status_code= status.HTTP_401_UNAUTHORIZED,
            detail= "Invalid Password",
        )
    return user

def create_access_token(data:dict, expires_delta: timedelta | None=None):
    to_encode = data.copy()
    if expires_delta:
        expire = datetime.utcnow() + expires_delta
    else:
        expire = datetime.utcnow() + timedelta(minutes=15)
    to_encode.update({"exp":expire})
    encoded_jwt = jwt.encode(to_encode, SECRET_KEY, algorithm=ALGORITHM)
    return encoded_jwt
    
async def get_current_user(token: str = Depends(oauth_test)):
    splitted_token = token.split()[1]
    print(splitted_token)
    credential_exception = HTTPException(
            status_code= status.HTTP_400_BAD_REQUEST,
            detail= "Please give valid username",
            headers={"WWW-Authenticate":"Bearer"}
        )
    try:
        payload = jwt.decode(splitted_token, SECRET_KEY, algorithms=[ALGORITHM])
        username: str = payload.get("sub")
        if username is None:
            raise credential_exception
        token_data = TokenData(username=username)
    except JWTError as e:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"Token Authentication Failed: {str(e)}",
            headers={"WWW-Authenticate": "Bearer"}
        )
    user = get_user(fake_db, username=token_data.username)
    if user is None:
        raise HTTPException(
            status_code= status.HTTP_401_UNAUTHORIZED,
            detail= "Username not found or invalid",
            headers={"WWW-Authenticate":"Bearer"}
        )
    return user
    
async def get_current_active_user(current_user: User= Depends(get_current_user)):
    if current_user.disabled:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Not active user")
    return current_user

@app.post("/token", response_model=Token)
async def login_for_access_token(form_data: OAuth2PasswordRequestForm = Depends()):
    user = authenticate_user(fake_db, form_data.username, form_data.password)
    if not user:
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, 
                            detail="Incorrect username or password",
                            headers={"WWW-Authenticate":"Bearer"}
                            )
    access_token_expires = timedelta(minutes= ACCESS_TOKEN_EXPIRE_MINUTES)
    access_token = create_access_token(
            data={"sub":user.username}, expires_delta=access_token_expires
        )
    
    return{"access_token":access_token, "token_type": "Bearer Token"}

@app.get("/user/me")
async def get_me(current_user: User = Depends(get_current_active_user)):
    return current_user

@app.post("/upload")
def upload(json_data: str = Form(...), files: List[UploadFile] = File(...)):
    try:
        processed_json_data = json.loads(json_data)
        for file in files:
            try:
                if file.filename.endswith(".mp4"):
                    contents = file.file.read()
                    file_path = os.path.join(upload_directory, file.filename)
                    with open(file_path, 'wb') as f:
                        while contents := file.file.read(1024 * 1024):
                            f.write(contents)
            except Exception:
                return {"message": "There was an error uploading the file(s)"}
            finally:
                file.file.close()
    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=f"There was an error processing JSON data: {e}",
        )

    return JSONResponse(content=processed_json_data)

if __name__ == "__main__":
    uvicorn.run("main:app", reload=True, host="0.0.0.0", port=8848)