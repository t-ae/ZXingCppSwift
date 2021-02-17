import CZXingCpp

public enum ImageFormat: Int32 {
    case Lum  = 0
    case RGB  = 1
    case BGR  = 2
    case RGBX = 3
    case XRGB = 4
    case BGRX = 5
    case XBGR = 6
}

public func QRDecode(data: UnsafePointer<UInt8>, rows: Int32, cols: Int32, format: ImageFormat) -> String? {
    if let result = qr_decode(data, cols, rows, format.rawValue) {
        return CppString(result).toString()
    }
    return nil
}
