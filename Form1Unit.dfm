object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'World'
  ClientHeight = 428
  ClientWidth = 1022
  Color = clWindow
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 798
    Top = 192
    Width = 33
    Height = 41
    Align = alCustom
    Anchors = [akRight]
    Style = bsCommandLink
    TabOrder = 0
    OnClick = Button1Click
    ExplicitLeft = 779
  end
  object AddPanel: TPanel
    Left = 837
    Top = 0
    Width = 185
    Height = 428
    Align = alRight
    BorderStyle = bsSingle
    Color = clGradientInactiveCaption
    ParentBackground = False
    TabOrder = 1
    ExplicitLeft = 818
    DesignSize = (
      181
      424)
    object AddName: TLabeledEdit
      Left = 8
      Top = 40
      Width = 121
      Height = 21
      HelpType = htKeyword
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Name'
      EditLabel.Color = clMenu
      EditLabel.ParentColor = False
      TabOrder = 0
      Text = 'Type Name here'
    end
    object AddX: TLabeledEdit
      Left = 8
      Top = 80
      Width = 121
      Height = 21
      HelpType = htKeyword
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'X'
      EditLabel.Color = clMenu
      EditLabel.ParentColor = False
      TabOrder = 1
      Text = '0'
      OnKeyPress = AddXKeyPress
    end
    object AddY: TLabeledEdit
      Left = 8
      Top = 120
      Width = 121
      Height = 21
      HelpType = htKeyword
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'Y'
      EditLabel.Color = clMenu
      EditLabel.ParentColor = False
      TabOrder = 2
      Text = '0'
      OnKeyPress = AddYKeyPress
    end
    object AddOk: TButton
      Left = 96
      Top = 387
      Width = 75
      Height = 25
      Anchors = [akRight]
      Caption = 'Add character'
      TabOrder = 3
      OnClick = AddOkClick
    end
    object AddDelete: TButton
      Left = 96
      Top = 147
      Width = 75
      Height = 25
      Caption = 'Delete'
      TabOrder = 4
      Visible = False
      OnClick = AddDeleteClick
    end
    object Help: TMemo
      Left = 8
      Top = 178
      Width = 169
      Height = 203
      Lines.Strings = (
        'Add character firstly by click on '
        '"Add Character"'
        ''
        'Click Left Mouse Button to  '
        'select character.'
        ''
        'Click Right Mouse Button to give '
        'selected character order to '
        'move.'
        '')
      TabOrder = 5
    end
  end
  object Draw: TTimer
    Interval = 17
    OnTimer = DrawTimer
    Left = 776
    Top = 8
  end
  object Phys: TTimer
    Interval = 333
    OnTimer = PhysTimer
    Left = 776
    Top = 56
  end
end
