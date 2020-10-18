

def init_shibie_model():
    init()

def jiance(rgb_img, rgb_file, xray_img, xray_file, radar_img, radar_file):
    print(rgb_img)   # (H, W, C) C=4 rgba
    if len(rgb_img) > 0:
        jiance_run(rgb_img[::-1], rgb_file)
    if len(xray_img) > 0:
        jiance_run(xray_img[::-1], xray_file)
    if len(radar_img) > 0:
        jiance_run(radar_img[::-1], xray_file)

def shibie(rgb_img, rgb_file, xray_img, xray_file):
    if len(rgb_img) > 0:
        shibie_run(rgb_img[::-1], rgb_file)
    if len(xray_img) > 0:
        shibie_run(xray_img[::-1], xray_file)

def finish():
    pass
