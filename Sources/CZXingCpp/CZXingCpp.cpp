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

extern "C" {

cppstring * qr_decode(const unsigned char* data, int cols, int rows, int format) {
    auto imageView = ZXing::ImageView(data, cols, rows, intToImageFormat(format));

    ZXing::DecodeHints hints;
    hints.setFormats(ZXing::BarcodeFormat::QRCode);
    ZXing::Result result = ZXing::ReadBarcode(imageView, hints);

    if (!result.isValid()) {
        return nullptr;
    }

    return new std::string(toUTF8(result.text()));
}

}
