while True:
    try:
        height = int(input("Height: "))
        if (height > 0 and height <= 8):
            break
    except:
        pass
for blocks in range(height):
    print(f"{' ' * (height - blocks - 1)}{'#' * (blocks + 1)}  {'#' * (blocks + 1)}")
