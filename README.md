# hotpixels
Scans a raw image and reports hot pixels

Wrote this to support a DPRevived discussion.  Uses the LibRaw library to open a raw file, 
then walks the image data and reports pixels containing a value above a threshold, default 15000.
Reports the row-column coordinates of the pixel, and the channel (RGB) to which it belongs

## Releases

There's a release with a Windows executable, just the .exe file.  Download it and execute it
without parameters to see a Usage synopsis.  It doesn't need any other libraries, statically 
linked.

## Building

Requires 1) a compiled LibRaw library and 2) a g++ compiler.  You need to edit the Makefile
to point to the LibRaw directory.

## Running

This is a command-line program, you need to run CMD or Powershell in Windows, bash or some
other shell in Unix.  Assuming the hotpixels executable and the raw files you want to mess
with are in the current working directory, type:
```
$ ./hotpixels DSZ_6223.NEF 
```
and you'll get something like this:

```
hotpixel assessment, threshold = 15000
raw image dimensions: 6064x4040
hot pixel count: 0, maxval: 12502
```
Hmmm, 12502 is a rather high value for a capture taken behind the lenscap, so let's adjust the 
threshold and see what it is:

```
$ ./hotpixels DSZ_6223.NEF 12000
hotpixel assessment, threshold = 12000
raw image dimensions: 6064x4040
3972,1100: R
hot pixel count: 1, maxval: 12502
```
The default threshold is based on the assumption you're scanning 14-bit raws, so you should adjust that
if your raw files have a different bit-resolution.
