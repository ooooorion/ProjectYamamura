# `0x0250` near-miss sources

These 144 candidates are the open `DIFF` rows from the `0x0250` block. Each
file is the raw m2c candidate that compiled but did not reproduce the target
bytes; none is a match or is listed in `src/functions.tsv`.

The audit in [`docs/NEAR_0250.md`](../../../docs/NEAR_0250.md) records the
recovered functions, family analysis and first differences.

| File | Range | Bytes | Words | First diff | Family |
|---|---|---:|---:|---|---|
| `func_025070A4.c` | `025070A4..02507188` | 232 | 16/19 | `+0x1C` | other |
| `func_02507F5C.c` | `02507F5C..02507F70` | 24 | 1/4 | `+0x4` | other |
| `func_025080DC.c` | `025080DC..025081C0` | 232 | 2/39 | `+0x4` | other |
| `func_025081C4.c` | `025081C4..02508224` | 100 | 2/24 | `+0x8` | other |
| `func_02508330.c` | `02508330..025083C4` | 152 | 2/37 | `+0x8` | other |
| `func_025086E0.c` | `025086E0..02508734` | 88 | 2/21 | `+0x8` | other |
| `func_025089C0.c` | `025089C0..02508A44` | 136 | 9/34 | `+0x4` | other |
| `func_02508A68.c` | `02508A68..02508AEC` | 136 | 9/34 | `+0x4` | other |
| `func_02508B6C.c` | `02508B6C..02508C2C` | 196 | 1/29 | `+0x4` | 02508B6C cluster |
| `func_02508C30.c` | `02508C30..02508CDC` | 176 | 16/44 | `+0x8` | 02508B6C cluster |
| `func_02508CE0.c` | `02508CE0..02508D8C` | 176 | 16/44 | `+0x8` | 02508B6C cluster |
| `func_02508D90.c` | `02508D90..02508E30` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02508E34.c` | `02508E34..02508EE0` | 176 | 9/42 | `+0x8` | 02508B6C cluster |
| `func_02508EE4.c` | `02508EE4..02508F84` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02508F88.c` | `02508F88..02509028` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250902C.c` | `0250902C..025090CC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_025090D0.c` | `025090D0..02509170` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509174.c` | `02509174..02509214` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509218.c` | `02509218..025092B8` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_025092BC.c` | `025092BC..0250935C` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509360.c` | `02509360..02509400` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509404.c` | `02509404..025094A4` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_025094A8.c` | `025094A8..02509548` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250954C.c` | `0250954C..025095EC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_025095F0.c` | `025095F0..02509690` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509694.c` | `02509694..02509744` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_02509748.c` | `02509748..025097E8` | 164 | 16/41 | `+0x8` | 02508B6C cluster |
| `func_025097EC.c` | `025097EC..0250989C` | 180 | 17/45 | `+0x8` | 02508B6C cluster |
| `func_025098A0.c` | `025098A0..02509940` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_02509944.c` | `02509944..02509A04` | 196 | 12/48 | `+0x20` | 02508B6C cluster |
| `func_02509A08.c` | `02509A08..02509AD8` | 212 | 19/52 | `+0x20` | 02508B6C cluster |
| `func_02509ADC.c` | `02509ADC..02509BAC` | 212 | 19/52 | `+0x20` | 02508B6C cluster |
| `func_02509BB0.c` | `02509BB0..02509C70` | 196 | 12/48 | `+0x20` | 02508B6C cluster |
| `func_02509C74.c` | `02509C74..02509D44` | 212 | 19/52 | `+0x20` | 02508B6C cluster |
| `func_02509D48.c` | `02509D48..02509E18` | 212 | 19/52 | `+0x20` | 02508B6C cluster |
| `func_02509E1C.c` | `02509E1C..02509EDC` | 196 | 12/48 | `+0x20` | 02508B6C cluster |
| `func_02509EE0.c` | `02509EE0..02509FB0` | 212 | 19/52 | `+0x20` | 02508B6C cluster |
| `func_02509FB4.c` | `02509FB4..0250A064` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_0250A068.c` | `0250A068..0250A108` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A10C.c` | `0250A10C..0250A1AC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A1B0.c` | `0250A1B0..0250A260` | 180 | 17/45 | `+0x8` | 02508B6C cluster |
| `func_0250A264.c` | `0250A264..0250A304` | 164 | 16/41 | `+0x8` | 02508B6C cluster |
| `func_0250A308.c` | `0250A308..0250A3A8` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A3AC.c` | `0250A3AC..0250A44C` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A450.c` | `0250A450..0250A4F0` | 164 | 16/41 | `+0x8` | 02508B6C cluster |
| `func_0250A4F4.c` | `0250A4F4..0250A594` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A598.c` | `0250A598..0250A648` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_0250A64C.c` | `0250A64C..0250A6EC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A6F0.c` | `0250A6F0..0250A790` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A794.c` | `0250A794..0250A834` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A838.c` | `0250A838..0250A8D8` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A8DC.c` | `0250A8DC..0250A97C` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250A980.c` | `0250A980..0250AA20` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AA24.c` | `0250AA24..0250AAC4` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AAC8.c` | `0250AAC8..0250AB78` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_0250AB7C.c` | `0250AB7C..0250AC2C` | 180 | 17/45 | `+0x8` | 02508B6C cluster |
| `func_0250AC30.c` | `0250AC30..0250ACD0` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250ACD4.c` | `0250ACD4..0250AD74` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AD78.c` | `0250AD78..0250AE18` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AE1C.c` | `0250AE1C..0250AEBC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AEC0.c` | `0250AEC0..0250AF60` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250AF64.c` | `0250AF64..0250B004` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B008.c` | `0250B008..0250B0A8` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B0AC.c` | `0250B0AC..0250B14C` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B150.c` | `0250B150..0250B1F0` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B1F4.c` | `0250B1F4..0250B2A4` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_0250B2A8.c` | `0250B2A8..0250B358` | 180 | 22/45 | `+0xC` | 02508B6C cluster |
| `func_0250B35C.c` | `0250B35C..0250B3FC` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B400.c` | `0250B400..0250B4A0` | 164 | 15/41 | `+0x8` | 02508B6C cluster |
| `func_0250B4A4.c` | `0250B4A4..0250B574` | 212 | 32/53 | `+0x20` | 02508B6C cluster |
| `func_0250B578.c` | `0250B578..0250B648` | 212 | 32/53 | `+0x20` | 02508B6C cluster |
| `func_0250B64C.c` | `0250B64C..0250B730` | 232 | 37/58 | `+0x20` | 02508B6C cluster |
| `func_0250B734.c` | `0250B734..0250B818` | 232 | 37/58 | `+0x20` | 02508B6C cluster |
| `func_0250B81C.c` | `0250B81C..0250B8CC` | 180 | 24/45 | `+0x20` | 02508B6C cluster |
| `func_0250B8D0.c` | `0250B8D0..0250B980` | 180 | 24/45 | `+0x20` | 02508B6C cluster |
| `func_0250B984.c` | `0250B984..0250BA34` | 180 | 24/45 | `+0x20` | 02508B6C cluster |
| `func_0250BA38.c` | `0250BA38..0250BAE8` | 180 | 24/45 | `+0x20` | 02508B6C cluster |
| `func_0250BB24.c` | `0250BB24..0250BB38` | 24 | 1/4 | `+0x4` | other |
| `func_0250BB3C.c` | `0250BB3C..0250BB78` | 64 | 2/15 | `+0x8` | other |
| `func_0250BB84.c` | `0250BB84..0250BC10` | 144 | 19/36 | `+0x8` | other |
| `func_0250BE88.c` | `0250BE88..0250BE9C` | 24 | 1/4 | `+0x4` | other |
| `func_0250C270.c` | `0250C270..0250C2EC` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250C2F0.c` | `0250C2F0..0250C368` | 124 | 5/30 | `+0x10` | +0x78 indexed field |
| `func_0250C36C.c` | `0250C36C..0250C3F0` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250C3F4.c` | `0250C3F4..0250C484` | 148 | 12/34 | `+0x10` | +0x78 indexed field |
| `func_0250C488.c` | `0250C488..0250C4F4` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250C4F8.c` | `0250C4F8..0250C564` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250C568.c` | `0250C568..0250C5F4` | 144 | 16/35 | `+0x40` | +0x78 indexed field |
| `func_0250C5F8.c` | `0250C5F8..0250C664` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250C668.c` | `0250C668..0250C700` | 156 | 15/38 | `+0x14` | +0x78 indexed field |
| `func_0250C704.c` | `0250C704..0250C788` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250C78C.c` | `0250C78C..0250C804` | 124 | 7/30 | `+0x14` | +0x78 indexed field |
| `func_0250C808.c` | `0250C808..0250C88C` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250C890.c` | `0250C890..0250C908` | 124 | 7/30 | `+0x14` | +0x78 indexed field |
| `func_0250C90C.c` | `0250C90C..0250C988` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250C98C.c` | `0250C98C..0250CA10` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250CA14.c` | `0250CA14..0250CA98` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250CA9C.c` | `0250CA9C..0250CB14` | 124 | 7/30 | `+0x14` | +0x78 indexed field |
| `func_0250CB18.c` | `0250CB18..0250CB9C` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250CBA0.c` | `0250CBA0..0250CC1C` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250CC20.c` | `0250CC20..0250CCAC` | 144 | 8/35 | `+0x1C` | +0x78 indexed field |
| `func_0250CEC8.c` | `0250CEC8..0250CF34` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250CF38.c` | `0250CF38..0250CFA4` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250CFA8.c` | `0250CFA8..0250D014` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D018.c` | `0250D018..0250D094` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250D098.c` | `0250D098..0250D124` | 144 | 7/35 | `+0x1C` | +0x78 indexed field |
| `func_0250D128.c` | `0250D128..0250D1AC` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250D1B0.c` | `0250D1B0..0250D234` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250D238.c` | `0250D238..0250D2BC` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250D2C0.c` | `0250D2C0..0250D32C` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D330.c` | `0250D330..0250D3AC` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250D3B0.c` | `0250D3B0..0250D43C` | 144 | 8/35 | `+0x1C` | +0x78 indexed field |
| `func_0250D440.c` | `0250D440..0250D4C8` | 140 | 13/34 | `+0x10` | +0x78 indexed field |
| `func_0250D4CC.c` | `0250D4CC..0250D548` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250D54C.c` | `0250D54C..0250D5B8` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D6C8.c` | `0250D6C8..0250D734` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D738.c` | `0250D738..0250D7A4` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D7A8.c` | `0250D7A8..0250D824` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250D828.c` | `0250D828..0250D8A4` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250D8A8.c` | `0250D8A8..0250D92C` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250D930.c` | `0250D930..0250D99C` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250D9A0.c` | `0250D9A0..0250DA0C` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250DA10.c` | `0250DA10..0250DA94` | 136 | 12/33 | `+0x10` | +0x78 indexed field |
| `func_0250DA98.c` | `0250DA98..0250DB84` | 240 | 7/59 | `+0x8` | +0x78 indexed field |
| `func_0250DB88.c` | `0250DB88..0250DBF4` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250DBF8.c` | `0250DBF8..0250DC7C` | 136 | 5/33 | `+0x10` | +0x78 indexed field |
| `func_0250DC80.c` | `0250DC80..0250DCFC` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250DD00.c` | `0250DD00..0250DD7C` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250DD80.c` | `0250DD80..0250DE04` | 136 | 5/33 | `+0x10` | +0x78 indexed field |
| `func_0250DE08.c` | `0250DE08..0250DE8C` | 136 | 5/33 | `+0x10` | +0x78 indexed field |
| `func_0250DE90.c` | `0250DE90..0250DF14` | 136 | 5/33 | `+0x10` | +0x78 indexed field |
| `func_0250DF18.c` | `0250DF18..0250DF84` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250DF88.c` | `0250DF88..0250DFF4` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250DFF8.c` | `0250DFF8..0250E090` | 156 | 7/38 | `+0x14` | +0x78 indexed field |
| `func_0250E094.c` | `0250E094..0250E12C` | 156 | 7/38 | `+0x14` | +0x78 indexed field |
| `func_0250E130.c` | `0250E130..0250E19C` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250E1A0.c` | `0250E1A0..0250E20C` | 112 | 5/27 | `+0x10` | +0x78 indexed field |
| `func_0250E210.c` | `0250E210..0250E28C` | 128 | 7/31 | `+0x14` | +0x78 indexed field |
| `func_0250E290.c` | `0250E290..0250E308` | 124 | 5/30 | `+0x10` | +0x78 indexed field |
| `func_0250E384.c` | `0250E384..0250E398` | 24 | 1/4 | `+0x4` | other |
| `func_0250E4C0.c` | `0250E4C0..0250E584` | 200 | 18/50 | `+0x8` | other |
| `func_0250E5C0.c` | `0250E5C0..0250E628` | 108 | 19/27 | `+0x14` | other |
| `func_0250E62C.c` | `0250E62C..0250E678` | 80 | 17/20 | `+0x14` | other |
| `func_0250FE00.c` | `0250FE00..0250FEA8` | 172 | 26/43 | `+0x8` | other |

Regenerate a candidate with `tools/crack.py`; do not treat these files as
verified source.
