from PIL import Image

def print_hello():
    print("hello")
    
def print_str(s):
    print(s)
    
def print_img(img):
    print(img.shape, img.sum())
    # r, g, b = img[:, :, 0], img[:, :, 1], img[:, :, 2]
    # img = img[::-1]
