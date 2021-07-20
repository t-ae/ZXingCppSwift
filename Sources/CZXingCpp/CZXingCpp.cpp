#include "include/CZXingCpp.h"

#include <string>
#include <locale>
#include <codecvt>

#include <CppZXingCpp/CppZXingCpp.h>

std::string toUTF8(const std::wstring & wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    return convert.to_bytes(wstr);
}

ZXing::ImageFormat intToImageFormat(int format) {
    switch (format) {
        case 0:
            return ZXing::ImageFormat::Lum;
        case 1:
            return ZXing::ImageFormat::RGB;
        case 2:
            return ZXing::ImageFormat::BGR;
        case 3:
            return ZXing::ImageFormat::RGBX;
        case 4:
            return ZXing::ImageFormat::XRGB;
        case 5:
            return ZXing::ImageFormat::BGRX;
        case 6:
            return ZXing::ImageFormat::XBGR;
        default:
            return ZXing::ImageFormat::None;
    }
}

ZXing::Binarizer intToBinarizer(int binarizer) {
    switch (binarizer) {
        case 0:
            return ZXing::Binarizer::LocalAverage;
        case 1:
            return ZXing::Binarizer::GlobalHistogram;
        case 2:
            return ZXing::Binarizer::FixedThreshold;
        case 3:
            return ZXing::Binarizer::BoolCast;
        default:
            return ZXing::Binarizer::LocalAverage;
    }
}

extern "C" {

cppstring * qr_decode(const unsigned char* data, int cols, int rows, int format, int binarizer) {
    auto imageView = ZXing::ImageView(data, cols, rows, intToImageFormat(format));

    ZXing::DecodeHints hints;
    hints.setFormats(ZXing::BarcodeFormat::QRCode);
    hints.setBinarizer(intToBinarizer(binarizer));

    ZXing::Result result = ZXing::ReadBarcode(imageView, hints);

    if (!result.isValid()) {
        return nullptr;
    }

    return new std::string(toUTF8(result.text()));
}

void qr_encode(const uint8_t* data, int length, int width, int height, uint8_t* image) {
    std::wstring str;
    ZXing::TextDecoder::Append(str, data, length, ZXing::CharacterSet::Unknown);
    auto writer = ZXing::MultiFormatWriter(ZXing::BarcodeFormat::QRCode);

    auto mat = writer.encode(str, width, height);
    auto bitmap = ZXing::ToMatrix<uint8_t>(mat);
    
    int i = 0;
    for(int y = 0 ; y < height ; y++) {
        for(int x = 0 ; x < width ; x++) {
            image[i++] = bitmap.get(x, y);
        }
    }
}

}
