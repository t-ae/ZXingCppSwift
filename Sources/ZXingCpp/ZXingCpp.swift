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

public enum Binarizer: Int32 {
    case localAverage       = 0
    case globalHistogram    = 1
    case fixedThreshold     = 2
    case boolCast           = 3
}

public func QRDecode(
    data: UnsafePointer<UInt8>,
    rows: Int32,
    cols: Int32,
    format: ImageFormat,
    binarizer: Binarizer = .localAverage
) -> String? {
    if let result = qr_decode(data, cols, rows, format.rawValue, binarizer.rawValue) {
        return CppString(result).toString()
    }
    return nil
}

public struct QRImage {
    public let width: Int
    public let height: Int
    public let data: [UInt8]
    
    public subscript(x: Int, y: Int) -> UInt8 {
        data[y * width + x]
    }
}

public func QREncode(
    string: String,
    width: Int,
    height: Int
) -> QRImage {
    var data = [UInt8](repeating: 0, count: width*height)
    var string = string
    
    data.withUnsafeMutableBufferPointer { data in
        string.withUTF8 { string in
            qr_encode(string.baseAddress!, Int32(string.count), Int32(width), Int32(height), data.baseAddress)
        }
    }
    
    return QRImage(width: width, height: height, data: data)
}
