object FrmServidor: TFrmServidor
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'SERVIDOR'
  ClientHeight = 603
  ClientWidth = 815
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 815
    Height = 603
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 329
      Width = 129
      Height = 19
      Caption = 'CLIENTES EM JOGO'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Calibri'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 8
      Top = 66
      Width = 118
      Height = 19
      Caption = 'CLIENTES ONLINE'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Calibri'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SbStatusServidor: TStatusBar
      Left = 1
      Top = 583
      Width = 813
      Height = 19
      Panels = <
        item
          Text = '  APLICA'#199#195'O SERVIDOR'
          Width = 250
        end
        item
          Text = '  DESATIVADO'
          Width = 200
        end
        item
          Width = 50
        end>
    end
    object BtnEnviarMsg: TButton
      Left = 656
      Top = 528
      Width = 143
      Height = 39
      Caption = 'ENVIAR'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Calibri'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BtnEnviarMsgClick
    end
    object EdtMsgGlobal: TEdit
      Left = 319
      Top = 533
      Width = 331
      Height = 27
      Hint = 'Mensagem para todos'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
    end
    object MemHistorico: TMemo
      Left = 319
      Top = 8
      Width = 480
      Height = 514
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 3
    end
    object BitBtnLimpar: TBitBtn
      Left = 281
      Top = 8
      Width = 32
      Height = 32
      Hint = 'Limpar Hist'#243'rico do Chat'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Glyph.Data = {
        36100000424D3610000000000000360000002800000020000000200000000100
        20000000000000100000C40E0000C40E00000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000010000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000004000000080000000C0000000F0000001200000014000000150000
        001600000016000000160000001400000013000000100000000D0000000A0000
        0006000000010000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000050000000B0000
        0010000000160000001A0000001F0000002300000026000000290000002B0000
        002C0000002C0000002B0000002A0000002800000024000000210000001D0000
        0018000000130000000D00000007000000010000000000000000000000000000
        0000000000000000000000000000000000040000000B00000012000000180000
        001F000000250000002B000000310000003500A0C4FF00A0C4FF000000400000
        004100000041000000400000003E0000003B00000038000000330000002E0000
        0028000000220000001C000000150000000E0000000700000000000000000000
        00000000000000000000000000050000000C000000140000001C000000230000
        002A00000032000000390000004000A0C4FFA3E8F1FF76CCDFFFA3E8F1FF00A0
        C4FF00A0C4FF00000056000000530000004E00000049000000430000003C0000
        00350000002E000000270000001F000000180000001000000008000000000000
        0000000000000000000100000009000000110000001900000021000000290000
        0031000000390000004100A0C4FFA3E8F1FF00A2C5FF53D5E6FF53D5E6FF00A0
        C4FFA3E8F1FFA3E8F1FF00A0C4FF0000005C000000540000004D000000450000
        003D000000350000002D000000250000001D000000150000000D000000000000
        0000000000000000000100000009000000110000001900000021000000290000
        00310000003A0000004178DEEBFF01A6C8FF03C2DAFF53D5E6FF00A0C4FF05C3
        DBFF53D5E6FF00A0C4FF9EE7F1FFA3E8F1FF00A0C4FF0000004D000000450000
        003D000000350000002D000000250000001D000000150000000D000000000000
        00000000000000000000000000050000000D000000150000001C000000240000
        002C0000003300A0C4FF78DEEBFF01AACBFF04C2DAFF00A0C4FF0EC9E1FF5ADA
        EBFF56D8E8FF00A0C4FF53D5E6FF02B1D0FF78DEEBFF03C2DAFF00A0C4FF0000
        00360000002F0000002800000020000000180000001100000009000000000000
        0000000000000000000000000000000000050000000C000000130000001A0000
        00200000002778DEEBFF53D5E6FF06C4DCFF5CDBEBFF02A4C6FF18D0E7FF5FDE
        EDFF00A0C4FF04C2DAFF53D5E6FF00A0C4FF03C2DAFF53D5E6FFA3E8F1FF00A0
        C4FF000000240000001D000000160000000F0000000800000001000000000000
        00000000000000000000000000000000000000000000000000060000000C0000
        001200A0C4FF78DEEBFF03B2D1FF12CCE3FF3BD8EBFF20D5EDFF20D5EDFF63E0
        F1FF12CCE4FF55D7E7FF00A0C4FF03C2DAFF53D5E6FF53D5E6FF00A0C4FF00A0
        C4FF00A0C4FF0000000F00000009000000030000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000100A0C4FF03C2DAFF0BBBD7FF1ED4EBFF0CB2D2FF2ADCF3FF28DAF2FF00A0
        C4FF15CEE5FF01A4C7FF03C2DAFF03C2DAFF53D5E6FF00A1C5FF53D5E6FF53D5
        E6FFA3E8F1FF00A0C4FF00000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000065DAE8FF0FCAE2FF1ED4EBFF2ADCF3FF14B9D8FF34E2F9FF04A4C7FF24D8
        EFFF06ADCDFF06C4DCFF03C2DAFF53D5E6FF01A5C8FF53D5E6FFA3E8F1FF00A0
        C4FF00A0C4FF0000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00007CE1EEFF1CD2EAFF2BDCF3FF37E4FBFF3EE7FDFF3CE6FDFF07A8CBFF26D9
        F0FF08B0D0FF04C3DBFF53D5E6FF01ABCBFF53D5E6FFA3E8F1FF00A0C4FF0000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000000000A0
        C4FF82E5F2FF27D8EFFF37E4FBFF2CCEE9FF4CE8FDFF18B9D8FF35E3FAFF13BD
        DAFF13CDE4FF53D5E6FF01B0CEFF52D5E6FFA3E8F1FF00A0C4FF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000000000A0
        C4FF88E9F6FF34E2F9FF48E8FDFF3ED5EDFF57EAFDFF49E8FDFF22CCE7FF23D7
        EEFF5BDBEBFF02B4D1FF03C2DAFFA3E8F1FF00A0C4FF00000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000000000000689A00A0
        C4FF8EEDFAFF41E7FDFF4EE1F5FF66ECFEFF3BCEE8FF48E8FDFF26D1ECFF1ED4
        EBFF07BCD8FF03C2DAFF9FE7F1FF00A0C4FF0000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000069FF0000C3FF0000
        69FF000069FF52E9FDFF66E9FBFF61E2F5FF5EEBFDFF3CE0F7FF2CDDF4FF16CB
        E4FF78DFECFF00A0C4FF00000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000000000000069FF0000C3FF0000
        C3FF1616D1FF000069FFB9F6FEFF74EDFEFF57EAFDFF3AE6FDFF26D9F0FF7FE3
        F0FF00A0C4FF0000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000A0C4FF000069FF0000
        69FF2121D9FF3A3AE9FF5353F9FF000069FF9FF3FEFF6CE9FAFF86E7F4FF00A0
        C4FF000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000A0C4FF41D1E3FF27D1E6FF4EE1
        F4FF000069FF4545F0FF5A5AFEFF4242E9FF2828D2FF000069FF00A0C4FF0000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000000A0C4FF50D7E8FF6EE3F2FF65EA
        FCFF70EDFDFF78EEFDFF000069FF3737E0FF1E1ECCFF000069FF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000000000000000000000A0C4FF91F1
        FDFF75EEFDFF7DEFFDFF7EEFFDFF000069FF000069FF00000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000002598FFF1A74ABFF00A0
        C4FF00A0C4FF9EF3FDFF9EF3FDFF00A0C4FF0000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000000000000000000000000002598FFF3388BDFF0E70ADFF0D6E
        A9FF02598FFF00A0C4FF00A0C4FF00A0C4FF0000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000002598F904C9BCEFF0F78B9FF0F75B4FF2D84
        BAFF02598FFF000000000000000000A0C4FF0000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000002598FFF107DC1FF107CC0FF0F7ABCFF0259
        8FFF000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000002598FFF72B3DBFF107DC1FF107DC1FF54A2D3FF0259
        8FFF000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000002598FFF75B4DBFF107DC1FF107DC1FF107DC1FF62A9D6FF0000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000002598FFF75B4DBFFFBFCFDFF02598FFF75B4DBFF02598FFF0000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000002598FFF75B4DBFF02598FFF02598FFF75B4DBFF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000002598FFF75B4DBFF75B4DBFF02598FFF000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000}
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = BitBtnLimparClick
    end
    object ListViewJogando: TListView
      Left = 8
      Top = 354
      Width = 305
      Height = 213
      Align = alCustom
      Columns = <
        item
          Caption = 'N'#176
          MaxWidth = 35
          MinWidth = 35
          Width = 35
        end
        item
          Alignment = taCenter
          AutoSize = True
          Caption = 'Jogador1'
        end
        item
          Alignment = taCenter
          Caption = 'VS.'
          MaxWidth = 40
          MinWidth = 40
          Width = 40
        end
        item
          Alignment = taCenter
          AutoSize = True
          Caption = 'Jogador 2'
        end>
      ColumnClick = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      ViewStyle = vsReport
    end
    object ListViewOnline: TListView
      Left = 8
      Top = 91
      Width = 305
      Height = 213
      Columns = <
        item
          Caption = 'N'#176
          MaxWidth = 35
          MinWidth = 35
          Width = 35
        end
        item
          Alignment = taCenter
          AutoSize = True
          Caption = 'Nome'
        end
        item
          Caption = #9658
          MaxWidth = 26
          MinWidth = 26
          Width = 26
        end
        item
          AutoSize = True
          Caption = 'Endere'#231'o'
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      ViewStyle = vsReport
    end
    object TglSwitchAtivar: TToggleSwitch
      Left = 8
      Top = 8
      Width = 101
      Height = 30
      Color = clGray
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      FrameColor = clGray
      ParentFont = False
      StateCaptions.CaptionOn = 'ON'
      StateCaptions.CaptionOff = 'OFF'
      SwitchHeight = 30
      SwitchWidth = 65
      TabOrder = 7
      ThumbColor = clWhite
      ThumbWidth = 30
      OnClick = TglSwitchAtivarClick
    end
  end
  object IdTCPServer: TIdTCPServer
    Bindings = <>
    DefaultPort = 5000
    OnConnect = IdTCPServerConnect
    OnDisconnect = IdTCPServerDisconnect
    OnExecute = IdTCPServerExecute
    Left = 224
    Top = 5
  end
end