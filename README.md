A image processing toolkit for BMP files providing image overlay, filtering, RGB channel separation, and bit extraction capabilities.

## Build

```bash
make
```

## Usage

```bash
bin/bmp_processor [COMMAND] [OPTIONS]
```

### Commands

#### help
Shows help message and exits.

```bash
bin/bmp_processor help
```

#### overlay
Overlays two images according to the specified option.

```bash
bin/bmp_processor overlay [OPTION] [IMAGE_1] [IMAGE_2] [OUTPUT_NAME]
```

**Options:**
- `and` - Logical AND operation overlay
- `or` - Logical OR operation overlay  
- `xor` - Logical XOR operation overlay

**Example:**
```bash
bin/bmp_processor overlay and image1.bmp image2.bmp output.bmp
```

#### filter
Applies the specified filter to the given image.

```bash
bin/bmp_processor filter [OPTION] [IMAGE] [OUTPUT_NAME]
```

**Options:**
- `smooth` - Smoothing filter
- `differential` - Differential filter
- `laplacian` - Laplacian filter

**Examples:**
```bash
bin/bmp_processor filter smooth input.bmp smoothed.bmp
bin/bmp_processor filter differential input.bmp differential.bmp
bin/bmp_processor filter laplacian input.bmp laplacian.bmp
```

#### separate
Separates the RGB channels of the given image.

```bash
bin/bmp_processor separate [IMAGE]
```

This command generates three files:
- `red.bmp` - Red channel
- `green.bmp` - Green channel
- `blue.bmp` - Blue channel

**Example:**
```bash
bin/bmp_processor separate input.bmp
```

#### extract
Extracts the specified bit position from the given image.

```bash
bin/bmp_processor extract [IMAGE] [BIT_POSITION] [OUTPUT_NAME]
```

**Parameters:**
- `BIT_POSITION` - Bit position to extract (0-7)

**Examples:**
```bash
bin/bmp_processor extract input.bmp 0 lsb.bmp
bin/bmp_processor extract input.bmp 7 msb.bmp
```

## Clean

```bash
make clean
```

Removes build files and object files.
