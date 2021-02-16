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

public struct Mat {
    public var data: UnsafePointer<UInt8>
    public var rows: Int32
    public var cols: Int32
    public var format: ImageFormat
    
    public init(data: UnsafePointer<UInt8>, rows: Int32, cols: Int32, format: ImageFormat) {
        self.data = data
        self.rows = rows
        self.cols = cols
        self.format = format
    }
}

public func QRDecode(mat: Mat) -> String? {
    if let result = qr_decode(mat.data, mat.cols, mat.rows, mat.format.rawValue) {
        return CppString(result).toString()
    }
    return nil
}
