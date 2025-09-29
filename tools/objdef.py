#!/usr/bin/env python3
from __future__ import annotations
import argparse
import codecs
from io import BufferedReader, BufferedWriter, BytesIO
import json
import math
import os
from pathlib import Path
import struct
import sys
from typing import TextIO

SCRIPT_DIR = Path(os.path.dirname(os.path.realpath(__file__)))
PROJECT_DIR = SCRIPT_DIR.parent

type BinTxtStruct = dict[int, tuple[str | None, str | None]]

class BinTxtRef:
    def __init__(self, 
                 datatype: str | None=None, 
                 comment: str | None=None, 
                 label: str | None=None,
                 pointer: str | None=None) -> None:
        self.datatype = datatype
        self.comment = comment
        self.label = label
        self.pointer = pointer

class BinTxt:
    def __init__(self) -> None:
        self.refs: dict[int, BinTxtRef] = {}
    
    def ref(self,
            offset: int, 
            datatype: str | None=None, 
            comment: str | None=None, 
            label: str | None=None,
            pointer: str | None=None):
        ref = self.refs.get(offset)
        if ref == None:
            ref = BinTxtRef(datatype, comment, label)
            self.refs[offset] = ref
        else:
            if datatype != None:
                ref.datatype = datatype
            if comment != None:
                ref.comment = comment
            if label != None:
                ref.label = label
            if pointer != None:
                ref.pointer = pointer
    
    def def_struct(self, offset: int, struct_type: BinTxtStruct):
        for (field_offset, (datatype, comment)) in struct_type.items():
            self.ref(offset + field_offset, datatype, comment)

OBJDEF_STRUCT: BinTxtStruct = {
    0x00: ("f32", "unk00"),
    0x04: ("f32", "scale"),
    0x08: (None, "pModelList"),
    0x0C: (None, "pTextures"),
    0x10: (None, "pSequenceBones"),
    0x14: (None, "unk14"),
    0x18: (None, "unk18"),
    0x1C: (None, "pSeq"),
    0x20: (None, "pEvent"),
    0x24: (None, "pHits"),
    0x28: (None, "pWeaponData"),
    0x2C: (None, "pAttachPoints"),
    0x30: (None, "pModLines"),
    0x34: (None, "pIntersectPoints"),
    0x38: (None, "nextIntersectPoint"),
    0x3C: (None, "nextIntersectLine"),
    0x40: (None, "unk40"),
    0x44: (None, "flags"),
    0x48: (None, "shadowType"),
    0x4A: (None, "shadowTexture"),
    0x4C: (None, "unk4C"),
    0x4D: (None, "unk4D"),
    0x4E: (None, "hitbox_flags60"),
    0x50: (None, "unk50"),
    0x52: (None, "unk52"),
    0x53: (None, "unk53"),
    0x54: (None, "unk54"),
    0x55: (None, "unk55"),
    0x56: (None, "numPlayerObjs"),
    0x57: (None, "unk57"),
    0x58: (None, "dllID"),
    0x5A: (None, "group"),
    0x5C: (None, "modLinesSize"),
    0x5D: (None, "numModels"),
    0x5E: (None, "unk5e"),
    0x5F: ("asciiz", "name"),
    0x6F: (None, "unk6f"),
    0x70: (None, "numAttachPoints"),
    0x71: (None, "numAnimatedFrames"),
    0x72: (None, "numSequenceBones"),
    0x73: (None, "stateVar73"),
    0x74: (None, "unk74"),
    0x75: (None, "unk75"),
    0x76: (None, "modLineCount"),
    0x78: (None, "modLineNo"),
    0x7A: (None, "numSequences"),
    0x7C: (None, None),
    0x84: (None, "unk84"),
    0x86: (None, "unk86"),
    0x87: (None, "unk87"),
    0x88: ("f32", "lagVar88"),
    0x8C: (None, "nLights"),
    0x8D: (None, "lightIdx"),
    0x8E: (None, "colorIdx"),
    0x8F: (None, "unk8F"),
    0x90: (None, "hitbox_flagsB6"),
    0x91: (None, None),
    0x93: (None, "unk93"),
    0x94: (None, "unk94"),
    0x96: (None, "unk96"),
    0x98: (None, None),
    0x9B: (None, "unk9b"),
    0x9C: (None, "unk9c"),
    0x9D: (None, "unk9d"),
    0x9E: (None, None),
    0xA0: (None, "unka0"),
    0xA2: (None, None),
    0xAC: (None, None),
}

def extract(file_offset: int, file_size: int, bin: BufferedReader, output: TextIO):
    bintxt = BinTxt()
    bintxt.def_struct(0x0, OBJDEF_STRUCT)

    data = bin.read(file_size)

    pModelList = struct.unpack_from(">I", data, 0x8)[0]
    numModels = struct.unpack_from(">b", data, 0x5D)[0]
    bintxt.ref(0x8, pointer="model_list")
    bintxt.ref(pModelList, label="model_list")
    for i in range(numModels):
        bintxt.ref(pModelList + (i * 4))
    model_list_end = pModelList + (numModels * 4)
    bintxt.ref(model_list_end, label=f"_unk{model_list_end:X}")

    refs = bintxt.refs.copy()

    if 0 not in refs:
        refs[0] = BinTxtRef()
    if file_size not in refs:
        refs[file_size] = BinTxtRef()
    
    refs = [t for t in refs.items()]
    refs.sort(key=lambda r: r[0])

    addr_width = len(hex(file_size)) - 2

    offset = 0
    i = 0
    while offset < file_size:
        (_, ref) = refs[i]
        size = refs[i + 1][0] - offset

        field_bytes = data[offset:offset + size]

        if ref.pointer != None and size == 4:
            directive = ".ptr"
            stride = size
        elif ref.datatype == "asciiz":
            directive = ".asciiz"
            stride = size
        elif ref.datatype == "ascii":
            directive = ".ascii"
            stride = size
        elif ref.datatype == "f32" and size % 4 == 0:
            directive = ".float"
            stride = 4
        elif size % 4 == 0:
            directive = ".word"
            stride = 4
        elif size % 2 == 0:
            directive = ".half"
            stride = 2
        else:
            directive = ".byte"
            stride = 1

        if ref.label != None:
            output.write(f"{ref.label}:\n")

        line = "/* "
        line += f"{offset:X}".rjust(addr_width, "0")
        line += f" */ {directive} "
        
        k = 0
        while k < size:
            if directive == ".ptr":
                literal = ref.pointer
            elif directive == ".asciiz":
                literal = f"\"{field_bytes[:-1].replace(b"\0", b"\\0").decode()}\""
            elif directive == ".ascii":
                literal = f"\"{field_bytes.replace(b"\0", b"\\0").decode()}\""
            elif directive == ".float":
                literal = str(struct.unpack_from(">f", field_bytes, k)[0])
            elif directive == ".word":
                literal = f"0x{struct.unpack_from(">I", field_bytes, k)[0]:08X}"
            elif directive == ".half":
                literal = f"0x{struct.unpack_from(">H", field_bytes, k)[0]:04X}"
            else:
                literal = f"0x{struct.unpack_from(">B", field_bytes, k)[0]:02X}"

            if k > 0:
                line += ", "

            line += literal
            k += stride

        if ref.comment != None:
            line = line.ljust(35)
            line += f" ; {ref.comment}"

        line += "\n"
        output.write(line)

        offset += size
        i += 1

    # def read_f32():
    #     return struct.unpack(">f", bin.read(4))[0]
    # def read_u32():
    #     return struct.unpack(">I", bin.read(4))[0]
    # def read_s32():
    #     return struct.unpack(">i", bin.read(4))[0]
    # def read_u16():
    #     return struct.unpack(">H", bin.read(2))[0]
    # def read_s16():
    #     return struct.unpack(">h", bin.read(2))[0]
    # def read_u8():
    #     return struct.unpack(">B", bin.read(1))[0]
    # def read_s8():
    #     return struct.unpack(">b", bin.read(1))[0]

    # data = {}

    # data['unk0'] = read_f32()
    # data['scale'] = read_f32()
    # data['pModelList'] = read_u32()
    # data['pTextures'] = read_u32()
    # data['pSequenceBones'] = read_u32()
    # data['unk14'] = read_u32()
    # data['unk18'] = read_u32()
    # data['pSeq'] = read_u32()
    # data['pEvent'] = read_u32()
    # data['pHits'] = read_u32()
    # data['pWeaponData'] = read_u32()
    # data['pAttachPoints'] = read_u32()
    # data['pModLines'] = read_u32()
    # data['pIntersectPoints'] = read_u32()
    # data['nextIntersectPoint'] = read_u32()
    # data['nextIntersectLine'] = read_u32()
    # data['unk40'] = read_u32()
    # data['flags'] = read_u32()
    # data['shadowType'] = read_u16()
    # data['shadowTexture'] = read_u16()
    # data['unk4C'] = read_u8()
    # data['unk4D'] = read_u8()
    # data['hitbox_flags60'] = read_u16()
    # data['unk50'] = read_u16()
    # data['unk52'] = read_u8()
    # data['unk53'] = read_u8()
    # data['unk54'] = read_u8()
    # data['unk55'] = read_u8()
    # data['numPlayerObjs'] = read_u8()
    # data['unk57'] = read_u8()
    # data['dllID'] = read_u16()
    # assert(bin.tell() - file_offset == 0x5a)
    # data['group'] = read_s16()
    # data['modLinesSize'] = read_s8()
    # data['numModels'] = read_s8()
    # data['unk5e'] = read_s8()
    # data['name'] = bin.read(16).decode(errors="replace")
    # assert(bin.tell() - file_offset == 0x6f)
    # data['unk6f'] = read_u8()
    # data['numAttachPoints'] = read_u8()
    # data['numAnimatedFrames'] = read_u8()
    # data['numSequenceBones'] = read_u8()
    # data['stateVar73'] = read_u8()
    # data['unk74'] = read_u8()
    # data['unk75'] = read_u8()
    # data['modLineCount'] = read_s16()
    # data['modLineNo'] = read_s16()
    # data['numSequences'] = read_s16()
    # data['hitboxFlags_7C'] = read_s16()
    # data['_unk7E'] = [read_s16(), read_s16(), read_s16()]
    # data['unk84'] = read_s16()
    # data['unk86'] = read_u8()
    # data['unk87'] = read_u8()
    # data['lagVar88'] = read_f32()
    # data['nLights'] = read_u8()
    # data['lightIdx'] = read_u8()
    # data['colorIdx'] = read_u8()
    # data['unk8F'] = read_u8()
    # data['hitbox_flagsB6'] = read_u8()
    # data['_unk91'] = [read_u8(), read_u8()]
    # data['hitboxFlags93'] = read_s8()
    # data['unk94'] = read_s16()
    # data['unk96'] = read_s16()
    # data['_unk98'] = [read_u8(), read_u8(), read_u8()]
    # data['unk9b'] = read_u8()
    # data['unk9c'] = read_u8()
    # data['unk9d'] = read_u8()
    # data['_unk9e'] = [read_u8(), read_u8()]
    # data['unka0'] = read_s16()
    # data['_unk98'] = [read_u8(), read_u8(), read_u8(), read_u8(), read_u8(), read_u8(), read_u8(), read_u8(), read_u8(), read_u8()]
    # assert(bin.tell() - file_offset == 0xAC)

    # if data['pEvent'] != 0:
    #     bin.seek(file_offset + data['pEvent'], os.SEEK_SET)
    #     evts = []
    #     data['pEvent'] = evts
    #     while (evt_id := read_s16()) != -1:
    #         read_s16()
    #         read_s16()
    #         # evt = {'id': evt_id}
    #         # evt['fileOffsetInBytes'] = read_s16()
    #         # evt['sizeInBytes'] = read_s16()
    #         # evts.append(evt)
    #         evts.append(evt_id)
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # if data['pHits'] != 0:
    #     bin.seek(file_offset + data['pHits'], os.SEEK_SET)
    #     hits = []
    #     data['pHits'] = hits
    #     while (hit_id := read_s16()) != -1:
    #         read_s16()
    #         read_s16()
    #         # hit = {'id': hit_id}
    #         # hit['fileOffsetInBytes'] = read_s16()
    #         # hit['sizeInBytes'] = read_s16()
    #         # hits.append(hit)
    #         hits.append(hit_id)
    #     assert(bin.tell() - file_offset <= file_offset + file_size)
    
    # if data['pWeaponData'] != 0:
    #     bin.seek(file_offset + data['pWeaponData'], os.SEEK_SET)
    #     wpdata = []
    #     data['pWeaponData'] = wpdata
    #     while (wpdata_id := read_s16()) != -1:
    #         read_s16()
    #         read_s16()
    #         wpdata.append(wpdata_id)
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # models = []
    # bin.seek(file_offset + data['pModelList'], os.SEEK_SET)
    # data['pModelList'] = models
    # for _ in range(data['numModels']):
    #     models.append(read_u32())
    # assert(bin.tell() - file_offset <= file_offset + file_size)

    # texs = []
    # bin.seek(file_offset + data['pTextures'], os.SEEK_SET)
    # data['pTextures'] = texs
    # for _ in range(data['numAnimatedFrames']*2):
    #     texs.append(read_u8())
    # assert(bin.tell() - file_offset <= file_offset + file_size)
    
    # seqbones = []
    # bin.seek(file_offset + data['pSequenceBones'], os.SEEK_SET)
    # data['pSequenceBones'] = seqbones
    # for _ in range(data['numSequenceBones'] * (data['numModels']+1)):
    #     seqbones.append(read_u8())
    # assert(bin.tell() - file_offset <= file_offset + file_size)

    # if data['unk18'] != 0:
    #     bin.seek(file_offset + data['unk18'], os.SEEK_SET)
    #     unk18 = {}
    #     data['unk18'] = unk18

    #     unk18['unk0'] = read_u16()
    #     unk18['unk2'] = read_s16()
    #     unk18['unk4'] = read_u32()
    #     unk18['unk8'] = read_s8()
    #     unk18['unk9'] = read_u16()
    #     unk18['unkB'] = read_s8()
    #     unk18['unkC'] = read_u32()
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # if data['unk40'] != 0:
    #     bin.seek(file_offset + data['unk40'], os.SEEK_SET)
    #     unk40 = {}
    #     data['unk40'] = unk40

    #     unk40['unk0'] = read_s16()
    #     unk40['unk2'] = read_s16()
    #     unk40['unk4'] = read_s16()
    #     unk40['unk6'] = read_s16()
    #     unk40['unk8'] = read_s16()
    #     unk40['unkA'] = read_s16()
    #     unk40['unkC'] = read_u8()
    #     unk40['unkD'] = read_u8()
    #     unk40['unkE'] = read_u8()
    #     unk40['unkF'] = read_u8()
    #     unk40['unk10'] = read_u8()
    #     unk40['unk11'] = [read_s8(),read_s8(),read_s8(),read_s8()]
    #     unk40['unk15'] = read_u8()
    #     unk40['unk16'] = read_u8()
    #     unk40['unk17'] = read_u8()
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # if data['pSeq'] != 0:
    #     bin.seek(file_offset + data['pSeq'], os.SEEK_SET)
    #     pseq = []
    #     data['pSeq'] = pseq
    #     for _ in range(data['numSequences']):
    #         pseq.append(read_u16())
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # if data['pAttachPoints'] != 0:
    #     bin.seek(file_offset + data['pAttachPoints'], os.SEEK_SET)
    #     aps = []
    #     data['pAttachPoints'] = aps

    #     for _ in range(data['numAttachPoints']):
    #         ap = {}
    #         ap['x'] = read_f32()
    #         ap['y'] = read_f32()
    #         ap['z'] = read_f32()
    #         ap['yaw'] = read_s16()
    #         ap['pitch'] = read_s16()
    #         ap['roll'] = read_s16()
    #         ap['bones'] = [read_s8() for _ in range(6)]
    #         aps.append(ap)
    #     assert(bin.tell() - file_offset <= file_offset + file_size)

    # json.dump(data, output, indent=2)
    
    pass

def extract_tab(tab: BufferedReader, bin: BufferedReader, dir: Path):
    # tab.seek(0, os.SEEK_END)
    # num_objs = (tab.tell() // 4) - 2
    # tab.seek(0, os.SEEK_SET)
    # print(num_objs)
    i = 0
    while True:
        file_offset, file_size = struct.unpack(">II", tab.read(8))

        if file_size == 0xffffffff:
            break

        tab.seek(-4, os.SEEK_CUR)

        bin.seek(file_offset, os.SEEK_SET)

       # print(i)

        with open(dir.joinpath(f"{i}.s"), "w") as output:
            extract(file_offset, file_size, bin, output)

        i += 1
        if i > 10:
            break

def main():
    # parser = argparse.ArgumentParser()
    # parser.add_argument("index", type=int, help="The tab index to extract.")
    # parser.add_argument("--tab", type=argparse.FileType("rb"), help="The OBJECTS.tab file to read.", required=True)
    # parser.add_argument("--bin", type=argparse.FileType("rb"), help="The OBJECTS.bin file to read.", required=True)
    # parser.add_argument("-o", "--output", type=argparse.FileType("w"), help="The object def file to write.", required=True)

    # args = parser.parse_args()
    
    # extract(args.index, args.tab, args.bin, args.output)

    BASEROM_DIR = PROJECT_DIR.joinpath("../dinomod/baserom")
    DINOMOD_DIR = PROJECT_DIR.joinpath("../dinomod/patch-2025-1-1")

    OUT_BASEROM_DIR = PROJECT_DIR.joinpath("extract/objects_txt/baserom")
    OUT_DINOMOD_DIR = PROJECT_DIR.joinpath("extract/objects_txt/dinomod")

    OUT_BASEROM_DIR.mkdir(parents=True, exist_ok=True)
    OUT_DINOMOD_DIR.mkdir(parents=True, exist_ok=True)

    with open(BASEROM_DIR.joinpath("OBJECTS.tab"), "rb") as objects_tab, \
         open(BASEROM_DIR.joinpath("OBJECTS.bin"), "rb") as objects_bin:
        extract_tab(objects_tab, objects_bin, OUT_BASEROM_DIR)
    
    with open(DINOMOD_DIR.joinpath("OBJECTS.tab"), "rb") as objects_tab, \
         open(DINOMOD_DIR.joinpath("OBJECTS.bin"), "rb") as objects_bin:
        extract_tab(objects_tab, objects_bin, OUT_DINOMOD_DIR)

if __name__ == "__main__":
    main()
